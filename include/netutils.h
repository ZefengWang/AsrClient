#ifndef NETUTILS_H
#define NETUTILS_H

#include <QObject>
#include <QTcpSocket>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QSslCertificate>
#include <QThread>
#include <QString>
#include <QByteArray>

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
    void httpGetData(QNetworkRequest req);

public slots:
    void handleFinished(QNetworkReply*);
signals:
    void sendHttpData(QByteArray);
private:
    QNetworkAccessManager manager;
    QString result;
//    QByteArray byteArray;

};

#endif // NETUTILS_H
