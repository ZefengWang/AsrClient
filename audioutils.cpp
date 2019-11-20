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
}

AudioUtils::~AudioUtils()
{
    qDebug() << "~AudioUtils";
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

void AudioUtils::startAudio(QIODevice *voicedata)
{
    if (audio != nullptr)
        stopRecording();
    audio = new QAudioInput(format, this);
    connect(audio, SIGNAL(stateChanged(QAudio::State)), this, SLOT(handleStateChanged(QAudio::State)));
    connect(audio, SIGNAL(notify()), this, SIGNAL(notify()));
    audio->setBufferSize(4096);
    audio->setVolume(1.0);
    audio->setNotifyInterval(6000);
    audio->start(voicedata);
}

void AudioUtils::testtimer()
{
    qDebug() << "testtimer";
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

