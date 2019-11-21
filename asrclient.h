#ifndef ASRCLIENT_H
#define ASRCLIENT_H

#include <QWidget>
#include <QAudioRecorder>
#include <QBuffer>
#include <QByteArray>

#include "audioutils.h"
#include "configutils.h"
#include "audiothread.h"
#include "fileutils.h"
#include "netutils.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AsrClient; }
QT_END_NAMESPACE

class AsrClient : public QWidget
{
    Q_OBJECT

public:
    AsrClient(QWidget *parent = nullptr);
    ~AsrClient();

private slots:
    void on_start_clicked(bool checked);
    void replyNotify();
    void handleReadData();
    void handleReadData(int channel);
private:
    Ui::AsrClient *ui;
    AudioUtils audio;

    ConfigUtils config;
    AudioThread audioThread;
    FileUtils fileUtils;
    NetUtils netUtils;
    QBuffer buff;
    QByteArray byteArray;
    char * audioBuff;
//    QIODevice *  iodevice = nullptr;

};
#endif // ASRCLIENT_H
