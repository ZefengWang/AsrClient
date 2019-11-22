#include "asrclient.h"
#include "ui_asrclient.h"

#include <QDebug>


AsrClient::AsrClient(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AsrClient)
{
    ui->setupUi(this);
//    this->setWindowFlags(Qt::FramelessWindowHint);
//    showFullScreen();
    audio.setAudioParam(config.getSampleRate(),config.getChannel(),config.getSampleSize());
    connect(&audioio,SIGNAL(updateData(QByteArray)), this, SLOT(getAudioData(QByteArray)));
    connect(&http, SIGNAL(getHttpData(QByteArray)), this, SLOT(handleHttpData(QByteArray)));
    audioBuff = new char[65536];
}

AsrClient::~AsrClient()
{
    delete ui;
    delete [] audioBuff;
}


void AsrClient::on_start_clicked(bool checked)
{
    qDebug() << checked;
    if (checked){
        ui->start->setText("Stop");
        audioio.start();
        audio.startAudio(&audioio);
    }
    else{
        QFile file(config.getPcmName());
        file.open(QIODevice::WriteOnly|QIODevice::Truncate|QIODevice::Unbuffered);
        QDataStream ds(&file);
        ui->start->setText("Start");
        audioio.stop();
        audio.stopRecording();
        file.close();
        ui->rtText->setText("");
//        ui->jsonText->setHtml("");
    }
}

void AsrClient::getAudioData(QByteArray ba)
{
    static int size = 0;
    this->ba.append(ba);
    size += ba.length();
    if (size > 1024){
        this->ba.clear();
        ui->rtText->setText(QString("len of pcm: %1").arg(size));
        http.httpPostData(QNetworkRequest(QUrl("http://10.110.148.80:8080/last/asr")),this->ba);
        size = 0;
        this->update();
    }

}

void AsrClient::handleHttpData(QByteArray result)
{
    ui->asrText->setHtml(result.toStdString().c_str());
}

