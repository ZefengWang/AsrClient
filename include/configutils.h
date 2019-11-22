#ifndef CONFIGUTILS_H
#define CONFIGUTILS_H

#include <QObject>
#include <QSettings>
#include <QString>
#include <QFile>
#include <QTimer>
#include <QDir>
#include <QDate>
#include <QTime>

class ConfigUtils : public QObject
{
    Q_OBJECT
public:
    explicit ConfigUtils(QObject *parent = nullptr);
    ~ConfigUtils();

    QString getIp();
    int getPort();
    QString getHttpUrl();
    QString getMode();
    int getSampleRate();
    int getChannel();
    int getSampleSize();
    QString getPcmName();

signals:

public slots:

private:
    QSettings *settings;
    QDate date;
    QTime time;
    QString pcmPath;
    QString pcmFileStr;
    QDir dir;
private:
    void configPath();
    void configFile();
    void checkConfig();
};

#endif // CONFIGUTILS_H
