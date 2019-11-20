#include "asrclient.h"
#include "ui_asrclient.h"

#include <QDebug>


AsrClient::AsrClient(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AsrClient)
{
    ui->setupUi(this);
    //    showFullScreen();
    audio.setAudioParam(config.getSampleRate(),config.getChannel(),config.getSampleSize());
    buff.setBuffer(&byteArray);
    connect(&audio, SIGNAL(notify()), this, SLOT(replyNotify()));

    //    buff->open(QIODevice::ReadWrite);
    //    buff->setBuffer(ba);
    //    qDebug() << "AudioUtils";
    //    audio->startAudio((QIODevice **)&buff);
}

AsrClient::~AsrClient()
{
    delete ui;
}


void AsrClient::on_start_clicked(bool checked)
{
    qDebug() << checked;
    if (checked){
        ui->start->setText("Stop");
        buff.open(QIODevice::ReadWrite|QIODevice::Truncate);
        audio.startAudio(&buff);
    }
    else{
        ui->start->setText("Start");
        buff.close();
        audio.stopRecording();
    }
}

void AsrClient::replyNotify()
{
    qDebug() << "notify";
    qDebug() << byteArray.length();
    QFile file(config.getPcmName());
    file.open(QIODevice::WriteOnly);
    file.write(buff.readAll());
    buff.seek(0);
    ui->asrText->append(QString("len: %1   %2").arg(byteArray.length()).arg(file.size()));
    file.close();
//    buff.reset();
//    byteArray.resize(0);
//    buff.seek(0);
//    if (!byteArray.isEmpty() || !byteArray.isNull()){
//        byteArray.clear();
//        byteArray.resize(0);
//        byteArray.squeeze();
//    }
}
