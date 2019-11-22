#include "include/fileutils.h"

QFile FileUtils::log;
QFile FileUtils::pcm;
QFile FileUtils::asr;

FileUtils::FileUtils()
{

}

FileUtils::~FileUtils()
{

}

QFile &FileUtils::pcmFile()
{
    return pcm;
}

QFile &FileUtils::asrFile()
{
    return asr;
}

QFile &FileUtils::logFile()
{
    return log;
}
