#ifndef AUDIOUTILS_H
#define AUDIOUTILS_H

#include <QObject>
#include <QAudioInput>
#include <QFile>
#include <QTimer>
#include <QDir>
#include <QDate>
#include <QTime>
#include <QString>

class AudioUtils: public QObject
{
    Q_OBJECT
public:
    AudioUtils();
    ~AudioUtils();

    void testtimer();
    bool setAudioParam(int sampleRate,int channel, int sampleSize);
    void resetAudioBuffer();
signals:
    void notify();

public slots:
    void stopRecording();
    void handleStateChanged(QAudio::State newState);
    void handleNotify();

    QIODevice *  startAudio();
    void startAudio(QIODevice *voicedevice );


private:
    QTimer timer;
    QAudioFormat format;
    QAudioInput *audio = nullptr;
    int buffSize = 0;
    int notifyTime = 0;

};

#endif // AUDIOUTILS_H
