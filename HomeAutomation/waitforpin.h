#ifndef WAITFORPIN_H
#define WAITFORPIN_H

#include <QWidget>
#include <QtWidgets>
#include "CommInterface.h"

namespace Ui {
class waitForPin;
}

class waitForPin : public QWidget
{
    Q_OBJECT

public:
    waitForPin(QStackedWidget *parent, CommInterface &commRef);
    ~waitForPin();

private slots:
    void on_codeAccept_PushButton_clicked();

private:
    Ui::waitForPin *ui;
    CommInterface* commPtr;
    QStackedWidget* parentPtr;
};

#endif // WAITFORPIN_H
