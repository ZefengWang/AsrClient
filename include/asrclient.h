#ifndef ASRCLIENT_H
#define ASRCLIENT_H

#include <QWidget>
#include <QAudioRecorder>
#include <QBuffer>
#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include "include/audioutils.h"
#include "include/configutils.h"
#include "include/audiothread.h"
#include "include/fileutils.h"
#include "include/netutils.h"
#include "include/audioio.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AsrClient; }
QT_END_NAMESPACE

class AsrClient : public QWidget
{
    Q_OBJECT

public:
    AsrClient(QWidget *parent = nullptr);
    ~AsrClient();
    void startRecord();
    void stopRecord();

private slots:
    void on_start_clicked(bool checked);
    void getAudioData(QByteArray ba);
    void handleHttpData(QByteArray result);
private:
    Ui::AsrClient *ui;
    AudioUtils audio;
    QByteArray ba;
    ConfigUtils config;
    AudioThread audioThread;
    FileUtils fileUtils;
    NetUtils netUtils;
    AudioIO audioio;
    HttpsClient http;
    QJsonArray json;
};
#endif // ASRCLIENT_H
