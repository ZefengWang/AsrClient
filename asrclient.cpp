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
        qDebug() << byteArray.length();
//        connect(&buff,SIGNAL(bytesWritten(int)), this, SLOT(handleReadData(int)));
        connect(&buff,SIGNAL(readyRead()), this, SLOT(handleReadData()));
        buff.open(QIODevice::ReadWrite|QIODevice::Unbuffered|QIODevice::Truncate);
        //iodevice =
        audio.startAudio(&buff);
    }
    else{
        QFile file(config.getPcmName());
        file.open(QIODevice::WriteOnly|QIODevice::Truncate|QIODevice::Unbuffered);
        //        file.write(buff.readAll());
        QDataStream ds(&file);
        ds << byteArray;
        ui->start->setText("Start");
        qDebug() << byteArray.length();

        audio.stopRecording();
        //        iodevice = nullptr;
        //        qDebug() << iodevice;
        file.close();
        buff.reset();
        buff.close();
    }
}

void AsrClient::replyNotify()
{
    //    qDebug() << "notify";

}

void AsrClient::handleReadData()
{
//    qDebug() << "handleReadData Before Read" << buff.data().length() << "  " <<buff.data().length();
    QByteArray ba ;
    do{
        qint64 len  = buff.read(audioBuff, 65536);
        qDebug() << len << "bytes had been read." << " isSequential: " << buff.isSequential();
    } while (!buff.atEnd());
    qDebug() << "handleReadData After Read" << buff.data().length() << "  " <<buff.data().length();


    //    buff.buffer().remove(0,buff.buffer().length());
    //    buff.readData(audioBuff,65536);
    //    buff.data().data();
    //    buff.seek(0);
    //    buff.reset();
    //    buff.readAll();
    //    qDebug( "%x",buff.buffer().data()[0]);
}

void AsrClient::handleReadData(int channel)
{
    qDebug() << "handleReadData Before Read" << buff.data().length() << "  " <<buff.data().length() << " channel: "<< channel;
    //    QByteArray ba = buff.read(buff.data().length());
    QByteArray ba ;
    //    buff.write(ba);
    do{
        qint64 len  = buff.read(audioBuff,65536);
        qDebug() << len << "bytes had been read.";
    } while (!buff.atEnd());
}
