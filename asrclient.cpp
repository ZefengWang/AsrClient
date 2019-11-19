#include "asrclient.h"
#include "ui_asrclient.h"
#include "configutils.h"

#include <QDebug>

AsrClient::AsrClient(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AsrClient)
{
    ui->setupUi(this);
    ConfigUtils config;
    showFullScreen();
//    showMaximized();
//    ui->textEdit->setText("ip: "+config.getIp());
    ui->textEdit->append("ip: "+config.getIp());
    ui->textEdit->append("port: "+QString("%1").arg(config.getPort()));
//    qDebug() << config.getPort();
//    qDebug() << QString("%1").arg(config.getPort());
    AudioUtils *audio = new AudioUtils;
}

AsrClient::~AsrClient()
{
    delete audio;
    delete ui;
}

