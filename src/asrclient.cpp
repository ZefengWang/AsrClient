#include "include/asrclient.h"
#include "ui_asrclient.h"

#include <QDebug>
#include <QSsl>


AsrClient::AsrClient(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AsrClient)
{
    ui->setupUi(this);
//    showFullScreen();
    audio.setAudioParam(config.getSampleRate(),config.getChannel(),config.getSampleSize());
    connect(&audioio,SIGNAL(sendAudioData(QByteArray)), this, SLOT(handleAudioData(QByteArray)));
    connect(&http, SIGNAL(sendHttpData(QByteArray)), this, SLOT(handleHttpData(QByteArray)));
}

AsrClient::~AsrClient()
{
    delete ui;
}

void AsrClient::startRecord()
{
    fileUtils.pcmFile().setFileName(config.getPcmName());
    fileUtils.pcmFile().open(QIODevice::WriteOnly|QIODevice::Truncate);
    audioio.start();
    audio.startAudio(&audioio);
}

void AsrClient::stopRecord()
{
    audioio.stop();
    audio.stopRecording();
    fileUtils.pcmFile().close();
    ui->rtText->setText("");
}


void AsrClient::on_start_clicked(bool checked)
{
    if (checked){
        startRecord();
        ui->start->setText("Stop");
    }
    else {
        stopRecord();
        ui->start->setText("Start");
    }
}

void AsrClient::handleAudioData(QByteArray ba)
{
    static int size = 0;
    fileUtils.pcmFile().write(ba);
    this->ba.append(ba);
    size += ba.length();
    if (size > 32000) {
//        QNetworkRequest netReq(QUrl(config.getHttpUrl()));
        QNetworkRequest netReq(QUrl("https://www.qt.io/"));
//        netReq.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
//        qDebug() << QSslSocket::supportsSsl() << QSslSocket::sslLibraryBuildVersionString() << QSslSocket::sslLibraryVersionString();
//        http.httpPostData(netReq,QByteArray());
        http.httpGetData(netReq);
        this->ba.clear();
        size = 0;
    }
}

void AsrClient::handleHttpData(QByteArray result)
{
//    QJsonParseError jsonError;
//    QJsonDocument jsDoc = QJsonDocument::fromJson(result, &jsonError);
//    if (jsonError.error != QJsonParseError::NoError) {
////        qDebug() << "json trans failed!";
//    }
//    ui->asrText->setAcceptRichText(true);
    ui->asrText->setHtml(result);
//    QJsonObject jsObj = jsDoc.object();
//    QStringList keys = jsObj.keys();
//    ui->jsonText->clear();
//    for (int i = 0; i < keys.length(); ++i) {
//        ui->jsonText->append(QString("%1\t:%2").arg(keys.at(i)).arg(jsObj.value(keys.at(i)).toVariant().toString()));
//    }
//    ui->asrText->setText(jsObj.value("rawText").toVariant().toString());
}
