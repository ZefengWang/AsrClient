#include "include/asrclient.h"

#include <QApplication>
#include <QCoreApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    AsrClient w;
    w.show();
    return a.exec();
}
