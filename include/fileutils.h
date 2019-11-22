#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <QObject>
#include <QFile>


class FileUtils: public QObject
{
    Q_OBJECT
public:
    FileUtils();
    ~FileUtils();
    QFile &pcmFile();
    QFile &asrFile();
    QFile &logFile();

signals:
public slots:

private:
     static QFile pcm;
     static QFile asr;
     static QFile log;

};

#endif // FILEUTILS_H
