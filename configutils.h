#ifndef CONFIGUTILS_H
#define CONFIGUTILS_H

#include <QObject>
#include <QSettings>
#include <QString>

class ConfigUtils : public QObject
{
    Q_OBJECT
public:
    explicit ConfigUtils(QObject *parent = nullptr);
    ~ConfigUtils();

    QString getIp();
    int getPort();
    QString getDomin();
    QString getMode();
    int getSampleRate();
    int getChannel();
    int getSampleSize();

    void checkConfig();

signals:

public slots:

private:
    QSettings *settings;
};

#endif // CONFIGUTILS_H
