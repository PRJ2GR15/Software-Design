#include "waitforpin.h"
#include "ui_waitforpin.h"

waitForPin::waitForPin(QStackedWidget *parent, CommInterface &commRef) :
    QWidget(parent),
    ui(new Ui::waitForPin)
{
    ui->setupUi(this);
    this->setAccessibleName("Wait4Pin");
    commPtr = &commRef;
    parentPtr = parent;
}

waitForPin::~waitForPin()
{
    delete ui;
}

void waitForPin::on_codeAccept_PushButton_clicked()
{
    if(commPtr->validatePin())
    {
        commPtr->getAllUnits();
        parentPtr->setCurrentIndex(0);
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Pin ikke godkendt.");
        msgBox.addButton(QMessageBox::Ok);
        msgBox.setText("Korrekt pin er IKKE indtastet.");
        if(msgBox.exec()==QMessageBox::Ok)
        {
            for(int i = 0; i < parentPtr->count(); ++i) {
                if(parentPtr->widget(i)->accessibleName().compare("Wait4Pin") == 0) {
                    parentPtr->setCurrentIndex(i);
                    return;
                }
            }
        }
    }
}
