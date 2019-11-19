#ifndef NETUTILS_H
#define NETUTILS_H

#include <QObject>
#include <QTcpSocket>

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

class HttpsClient: public QObject
{
    Q_OBJECT
public:
    HttpsClient();
    ~HttpsClient();
};

#endif // NETUTILS_H
