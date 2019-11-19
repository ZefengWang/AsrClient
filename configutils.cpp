#include "configutils.h"
#include <QCoreApplication>

ConfigUtils::ConfigUtils(QObject *parent) : QObject(parent)
{
    QCoreApplication::setOrganizationName("Lenovo");
    QCoreApplication::setOrganizationDomain("www.lenovo.com");
    QCoreApplication::setApplicationName("ASR Client");
    settings = new QSettings("config.ini", QSettings::IniFormat);
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

QString ConfigUtils::getDomin()
{
    if (settings->contains("Https/Domin"))
        return settings->value("Https/Domin").toString();
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

void ConfigUtils::checkConfig()
{
    if (!settings->contains("Socket/Ip"))
        settings->setValue("Socket/Ip", "10.110.148.56");
    if (!settings->contains("Socket/Port"))
        settings->setValue("Socket/Port", 5010);
    if (!settings->contains("Https/Domin"))
        settings->setValue("Https/Domin", "https://www.lenovo.com");
    if (!settings->contains("Mode/Mode"))
        settings->setValue("Mode/Mode", "socket");
    if (!settings->contains("Audio/SampleRate"))
        settings->setValue("Audio/SampleRate", 16000);
    if (!settings->contains("Audio/Channel"))
        settings->setValue("Audio/Channel", 1);
    if (!settings->contains("Audio/SampleSize"))
        settings->setValue("Audio/SampleSize", 16);
}

