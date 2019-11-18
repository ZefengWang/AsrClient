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

#endif // NETUTILS_H
