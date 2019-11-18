#include "asrclient.h"

#include <QApplication>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("Lenovo");
    QCoreApplication::setOrganizationDomain("www.lenovo.com");
    QCoreApplication::setApplicationName("ASR Client");
    QApplication a(argc, argv);
    AsrClient w;
    w.show();
    return a.exec();
}
