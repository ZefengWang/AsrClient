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
public:

private:
    QFile pcm;
    QFile ASR;
    QFile log;

};

#endif // FILEUTILS_H
