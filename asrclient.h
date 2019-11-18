#ifndef ASRCLIENT_H
#define ASRCLIENT_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class AsrClient; }
QT_END_NAMESPACE

class AsrClient : public QWidget
{
    Q_OBJECT

public:
    AsrClient(QWidget *parent = nullptr);
    ~AsrClient();

private:
    Ui::AsrClient *ui;
};
#endif // ASRCLIENT_H
