#include "netutils.h"

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

void HttpsClient::handleFinished(QNetworkReply * httpResult)
{
//    qDebug() <<httpResult->rawHeaderPairs();
    emit getHttpData(httpResult->readAll());
    httpResult->deleteLater();
}
