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
//    qreal m_level = 0.0; // 0.0 <= m_level <= 1.0
    QByteArray ba;

signals:
    void updateData(QByteArray);
};

#endif // AUDIOIO_H
