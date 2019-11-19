#ifndef AUDIOUTILS_H
#define AUDIOUTILS_H

#include <QObject>
#include <QAudioInput>
#include <QFile>
#include <QTimer>

class AudioUtils: public QObject
{
    Q_OBJECT
public:
    AudioUtils();
    ~AudioUtils();
public slots:
    void stopRecording();
    void handleStateChanged(QAudio::State newState);
    void testtimer();

private:
    QAudioInput *audio;
    QFile pcmFile;
    QTimer *timer;
};

#endif // AUDIOUTILS_H
