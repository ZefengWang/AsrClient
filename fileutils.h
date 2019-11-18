#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <QObject>
#include <QSettings>


class FileUtils: public QObject
{
    Q_OBJECT
public:
    FileUtils();
    ~FileUtils();
public:
    QSettings settings;
};

#endif // FILEUTILS_H
