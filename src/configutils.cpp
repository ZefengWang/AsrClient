#include "include/configutils.h"
#include <QCoreApplication>
#include <QDebug>

ConfigUtils::ConfigUtils(QObject *parent) : QObject(parent)
{
    QCoreApplication::setOrganizationName("Lenovo");
    QCoreApplication::setOrganizationDomain("www.lenovo.com");
    QCoreApplication::setApplicationName("AsrClient");
    settings = new QSettings("config.ini", QSettings::IniFormat);
    checkConfig();
    configPath();
    configFile();
}

ConfigUtils::~ConfigUtils()
{
    delete settings;
    settings = nullptr;
}

QString ConfigUtils::getIp()
{
    if (settings->contains("Socket/Ip"))
        return settings->value("Socket/Ip").toString();
    else
        return "0.0.0.0";
}

int ConfigUtils::getPort()
{
    if (settings->contains("Socket/Port"))
        return settings->value("Socket/Port").toInt();
    else
        return 5010;
}

QString ConfigUtils::getHttpUrl()
{
    if (settings->contains("Http/Protocol") &&
            settings->contains("Http/Ip") &&
            settings->contains("Http/Port") )
        return QString("%1://%2:%3/lasf/asr").\
                arg(settings->value("Http/Protocol").toString()).\
                arg(settings->value("Http/Ip").toString()).\
                arg(settings->value("Http/Port").toString());
    else
        return "";
}

QString ConfigUtils::getMode()
{
    if (settings->contains("Mode/Mode"))
        return settings->value("Mode/Mode").toString();
    else
        return "";
}

int ConfigUtils::getSampleRate()
{
    if (settings->contains("Audio/SampleRate"))
        return settings->value("Audio/SampleRate").toInt();
    else
        return 16000;
}

int ConfigUtils::getChannel()
{
    if (settings->contains("Audio/Channel"))
        return settings->value("Audio/Channel").toInt();
    else
        return 1;
}

int ConfigUtils::getSampleSize()
{
    if (settings->contains("Audio/SampleSize"))
        return settings->value("Audio/SampleSize").toInt();
    else
        return 16;
}

QString ConfigUtils::getPcmName()
{
    configPath();
    configFile();
    return pcmFileStr;
}

void ConfigUtils::configPath()
{
    date = QDate::currentDate();
    pcmPath = QString("./Record/%1/%2/%3").arg(date.year()).arg(date.month()).arg(date.day());
    if (!dir.exists(pcmPath)) {
        dir.mkpath(pcmPath);
    }
}

void ConfigUtils::configFile()
{
    time = QTime::currentTime();
    pcmFileStr = QString("%1/%2.pcm").arg(pcmPath).arg(time.toString("hh-mm-ss"));
}

void ConfigUtils::checkConfig()
{
    if (settings == nullptr)
        settings = new QSettings("config.ini", QSettings::IniFormat);
    if (!settings->contains("Socket/Ip"))
        settings->setValue("Socket/Ip", "10.110.148.56");
    if (!settings->contains("Socket/Port"))
        settings->setValue("Socket/Port", 5010);
    if (!settings->contains("Http/Protocol"))
        settings->setValue("Http/Protocol", "http");
    if (!settings->contains("Http/Ip"))
        settings->setValue("Http/Ip", "10.110.148.80");
    if (!settings->contains("Http/Port"))
        settings->setValue("Http/Port", "8080");
    if (!settings->contains("Mode/Mode"))
        settings->setValue("Mode/Mode", "socket");
    if (!settings->contains("Audio/SampleRate"))
        settings->setValue("Audio/SampleRate", 16000);
    if (!settings->contains("Audio/Channel"))
        settings->setValue("Audio/Channel", 1);
    if (!settings->contains("Audio/SampleSize"))
        settings->setValue("Audio/SampleSize", 16);
    if (!settings->contains("Param/cpf"))
        settings->setValue("Param/cpf", "multi");
    if (!settings->contains("Param/dtp"))
        settings->setValue("Param/dtp", "desktop");
    if (!settings->contains("Param/ver"))
        settings->setValue("Param/ver", "1.0.0");
    if (!settings->contains("Param/did"))
        settings->setValue("Param/did", "");
    if (!settings->contains("Param/uid"))
        settings->setValue("Param/uid", "1");
    if (!settings->contains("Param/dev"))
        settings->setValue("Param/dev", "asr.multi.desktop");
    if (!settings->contains("Param/app"))
        settings->setValue("Param/app", "asr.multi.desktop");
    if (!settings->contains("Param/stm"))
        settings->setValue("Param/stm", "0");
    if (!settings->contains("Param/ssm"))
        settings->setValue("Param/ssm", "false");
    if (!settings->contains("Param/vdm"))
        settings->setValue("Param/vdm", "all");
    if (!settings->contains("Param/rvr"))
        settings->setValue("Param/rvr", "");
    if (!settings->contains("Param/sec"))
        settings->setValue("Param/sec", "cmd");
    if (!settings->contains("Param/ntt"))
        settings->setValue("Param/ntt", "wire");
    if (!settings->contains("Param/aue"))
        settings->setValue("Param/aue", "pcm");
    if (!settings->contains("Param/auf"))
        settings->setValue("Param/auf", "audio/L;source=outer;rate=16000");
    if (!settings->contains("Param/ixid"))
        settings->setValue("Param/ixid", "0");
    if (!settings->contains("Param/pidx"))
        settings->setValue("Param/pidx", "1");
    if (!settings->contains("Param/over"))
        settings->setValue("Param/over", 0);
}

