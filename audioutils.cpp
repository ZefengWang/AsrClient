#include "audioutils.h"
#include <QAudioEncoderSettings>
#include <QDir>
#include <QDate>
#include <QTime>
#include <QDebug>


AudioUtils::AudioUtils()
{

    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    QString pcmPath = QString("./audio/%1/%2/%3").arg(date.year()).arg(date.month()).arg(date.day());
    QDir dir;
    timer = new QTimer(this);
    dir.mkpath(pcmPath);
    pcmFile.setFileName(QString("%1/%2.raw").arg(pcmPath).arg(time.toString("hh-mm-ss")));
    pcmFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
    qDebug() << pcmFile.isOpen() << pcmPath << pcmFile.fileName() << date.year();
    QAudioFormat format;
    // Set up the desired format, for example:
    format.setSampleRate(16000);
    format.setChannelCount(1);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
    if (!info.isFormatSupported(format)) {
        qWarning() << "Default format not supported, trying to use the nearest.";
        format = info.nearestFormat(format);
    }
    qDebug() << info.deviceName();
    audio = new QAudioInput(format, this);
//    connect(audio, SIGNAL(stateChanged(QAudio::State)), this, SLOT(handleStateChanged(QAudio::State)));
    //QTimer::singleShot(3000, this, SLOT(stopRecording()));
    qDebug() << connect(timer, SIGNAL(timeout()), this, SLOT(stopRecording()));
    qDebug() << connect(timer, SIGNAL(timeout()), this, SLOT(testtimer()));
    audio->start(&pcmFile);
    if (audio->state() == QAudio::ActiveState){
        qDebug() << audio->state() << audio->format();
        timer->setInterval(10000);
        timer->start();
    }
}

AudioUtils::~AudioUtils()
{
    delete timer;
}

void AudioUtils::stopRecording()
{
    if (audio->state() == QAudio::ActiveState) {
        timer->stop();
    qDebug() << "stopRecording";
    audio->stop();
    pcmFile.close();
    delete audio;
    }
}

void AudioUtils::handleStateChanged(QAudio::State newState)
{
    switch (newState) {
        case QAudio::StoppedState:
            if (audio->error() != QAudio::NoError) {
                // Error handling
                audio->stop();
                pcmFile.close();
                    qDebug() << "StoppedState";
            } else {
                qDebug() << "Finished";
                // Finished recording
            }
            break;

        case QAudio::ActiveState:
            // Started recording - read from IO device
            break;

        default:
            // ... other cases as appropriate
            break;
    }
}

void AudioUtils::testtimer()
{
    qDebug() << "testtimer";
}
