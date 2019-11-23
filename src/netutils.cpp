#include "include/netutils.h"
#include <QFile>

NetUtils::NetUtils()
{

}

NetUtils::~NetUtils()
{

}

TcpClient::TcpClient()
{

}

TcpClient::~TcpClient()
{

}

HttpsClient::HttpsClient()
{
    connect(&manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(handleFinished(QNetworkReply *)));
}

HttpsClient::~HttpsClient()
{

}

void HttpsClient::httpPostData(QNetworkRequest req, QByteArray ba)
{
    manager.post(req,ba);
}

void HttpsClient::httpGetData(QNetworkRequest req)
{
    manager.get(req);
}

void HttpsClient::handleFinished(QNetworkReply * httpResult)
{
    emit sendHttpData(httpResult->readAll());
    httpResult->deleteLater();
}
