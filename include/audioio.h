#ifndef AUDIOIO_H
#define AUDIOIO_H

#include <QObject>
#include <QIODevice>
#include <QByteArray>

class AudioIO : public QIODevice
{
    Q_OBJECT
public:
    AudioIO();
    void start();
    void stop();

//    qreal level() const;
    qint64 readData(char *data, qint64 maxlen) override;
    qint64 writeData(const char *data, qint64 len) override;

private:
    quint32 m_maxAmplitude = 0;
    QByteArray ba;

signals:
    void sendAudioData(QByteArray);
};

#endif // AUDIOIO_H
