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

void waitForPin::waitForValidate()
{
    bool validated = false;

    do
    {
        cout << "waitForPin:: in do while" << endl;
        validated = commPtr->validatePin();
        if(validated)
            break;
    } while(!validated);
    parentPtr->setCurrentIndex(0);

}
