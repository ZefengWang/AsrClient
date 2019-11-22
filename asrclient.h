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
#include "audioutils.h"
#include "configutils.h"
#include "audiothread.h"
#include "fileutils.h"
#include "netutils.h"
#include "audioio.h"

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
