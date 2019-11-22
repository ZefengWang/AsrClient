#include "audioutils.h"
#include <QAudioEncoderSettings>

#include <QDebug>

AudioUtils::AudioUtils()
{
    format.setSampleRate(16000);
    format.setChannelCount(1);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);
    notifyTime = 100;
    buffSize = 32*notifyTime;
}

AudioUtils::~AudioUtils()
{
    qDebug() << "~AudioUtils";
    disconnect(this);
    if (timer.isActive()){
        timer.stop();
        timer.disconnect();
    }
    if ((audio != nullptr) && (audio->state() != QAudio::StoppedState)) {
        audio->stop();
        audio->disconnect();
        delete audio;
    }
}

void AudioUtils::stopRecording()
{
    if (audio->state() != QAudio::StoppedState) {
        audio->stop();
    }
    audio->disconnect();
    delete audio;
    audio = nullptr;
}

void AudioUtils::handleStateChanged(QAudio::State newState)
{
    qDebug() << "handleStateChanged" ;
    switch (newState) {
    case QAudio::StoppedState:
        if (audio->error() != QAudio::NoError) {
            // Error handling
        } else {
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

QIODevice * AudioUtils::startAudio()
{
    if (audio != nullptr)
        stopRecording();
    audio = new QAudioInput(format, this);
    connect(audio, SIGNAL(stateChanged(QAudio::State)), this, SLOT(handleStateChanged(QAudio::State)));
//    connect(audio, SIGNAL(notify()), this, SLOT(handleNotify()));
    connect(audio, SIGNAL(notify()), this, SIGNAL(notify()));
    audio->setBufferSize(buffSize);
    audio->setVolume(1.0);
    audio->setNotifyInterval(notifyTime);
    QIODevice * d = audio->start();
    return d;
}

void AudioUtils::startAudio(QIODevice *voicedevice)
{
    if (audio != nullptr)
        stopRecording();
    audio = new QAudioInput(format, this);
    connect(audio, SIGNAL(stateChanged(QAudio::State)), this, SLOT(handleStateChanged(QAudio::State)));
    audio->setBufferSize(buffSize);
    qDebug() <<"buffer size" <<audio->bufferSize();
    audio->setVolume(1.0);
    qDebug() <<"volume" << audio->volume();
    qDebug() <<"notify interval" << audio->notifyInterval();
    audio->start(voicedevice);
}

bool AudioUtils::setAudioParam(int sampleRate, int channel, int sampleSize)
{
    format.setSampleRate(sampleRate);
    format.setChannelCount(channel);
    format.setSampleSize(sampleSize);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
    if (!info.isFormatSupported(format)) {
        qCritical() << "Default format not supported, trying to use the nearest.";
        format = info.nearestFormat(format);
        return false;
    }
    return true;
}

