#include "include/audioio.h"
#include <QDebug>

AudioIO::AudioIO()
{

}

void AudioIO::start()
{
    open(QIODevice::WriteOnly|QIODevice::Truncate);
}

void AudioIO::stop()
{
    close();
}

qint64 AudioIO::readData(char *data, qint64 maxlen)
{
    Q_UNUSED(data)
    Q_UNUSED(maxlen)

    return 0;
}

qint64 AudioIO::writeData(const char *data, qint64 len)
{
    QByteArray ba(QByteArray::fromRawData(data,static_cast<int>(len)));
    emit updateData(ba);
    return len;
}
