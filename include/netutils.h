#ifndef NETUTILS_H
#define NETUTILS_H

#include <QObject>
#include <QTcpSocket>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QThread>
#include <QString>

class NetUtils: public QObject
{
    Q_OBJECT
public:
    NetUtils();
    ~NetUtils();
};

class TcpClient: public QObject
{
    Q_OBJECT
public:
    TcpClient();
    ~TcpClient();
};

class HttpsClient: public QThread
{
    Q_OBJECT
public:
    HttpsClient();
    ~HttpsClient();
    void httpPostData(QNetworkRequest req, QByteArray ba);
public slots:
    void handleFinished(QNetworkReply*);
signals:
    void getHttpData(QByteArray);
private:
    QNetworkAccessManager manager;
    QString result;

};

#endif // NETUTILS_H
