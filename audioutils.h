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
signals:
    void notify();

public slots:
    void stopRecording();
    void handleStateChanged(QAudio::State newState);
    void startAudio(QIODevice *voicedata);


private:
    QTimer timer;
    QAudioFormat format;
    QAudioInput *audio = nullptr;

};

#endif // AUDIOUTILS_H
