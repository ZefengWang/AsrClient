#include "asrclient.h"
#include "ui_asrclient.h"

AsrClient::AsrClient(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AsrClient)
{
    ui->setupUi(this);
}

AsrClient::~AsrClient()
{
    delete ui;
}

