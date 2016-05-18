/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLuk;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *leftLayout;
    QPushButton *TilfojEnhed;
    QPushButton *RedigerEnhed;
    QPushButton *RedigerTidsplan;
    QPushButton *FjernEnhed;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *rightLayout;
    QTableWidget *myTable;
    QPushButton *opdaterStatus;
    QSpacerItem *horizontalSpacer_3;
    QMenuBar *menuBar;
    QMenu *menuHomeaumation;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(523, 387);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        actionLuk = new QAction(MainWindow);
        actionLuk->setObjectName(QStringLiteral("actionLuk"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(5, 10, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        leftLayout = new QVBoxLayout();
        leftLayout->setSpacing(6);
        leftLayout->setObjectName(QStringLiteral("leftLayout"));
        TilfojEnhed = new QPushButton(centralWidget);
        TilfojEnhed->setObjectName(QStringLiteral("TilfojEnhed"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(50);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(TilfojEnhed->sizePolicy().hasHeightForWidth());
        TilfojEnhed->setSizePolicy(sizePolicy1);

        leftLayout->addWidget(TilfojEnhed);

        RedigerEnhed = new QPushButton(centralWidget);
        RedigerEnhed->setObjectName(QStringLiteral("RedigerEnhed"));
        sizePolicy1.setHeightForWidth(RedigerEnhed->sizePolicy().hasHeightForWidth());
        RedigerEnhed->setSizePolicy(sizePolicy1);

        leftLayout->addWidget(RedigerEnhed);

        RedigerTidsplan = new QPushButton(centralWidget);
        RedigerTidsplan->setObjectName(QStringLiteral("RedigerTidsplan"));
        sizePolicy1.setHeightForWidth(RedigerTidsplan->sizePolicy().hasHeightForWidth());
        RedigerTidsplan->setSizePolicy(sizePolicy1);

        leftLayout->addWidget(RedigerTidsplan);

        FjernEnhed = new QPushButton(centralWidget);
        FjernEnhed->setObjectName(QStringLiteral("FjernEnhed"));
        sizePolicy1.setHeightForWidth(FjernEnhed->sizePolicy().hasHeightForWidth());
        FjernEnhed->setSizePolicy(sizePolicy1);

        leftLayout->addWidget(FjernEnhed);


        horizontalLayout->addLayout(leftLayout);

        horizontalSpacer = new QSpacerItem(15, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        rightLayout = new QVBoxLayout();
        rightLayout->setSpacing(6);
        rightLayout->setObjectName(QStringLiteral("rightLayout"));
        myTable = new QTableWidget(centralWidget);
        if (myTable->columnCount() < 3)
            myTable->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        myTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        myTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        myTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        myTable->setObjectName(QStringLiteral("myTable"));
        myTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        myTable->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        myTable->setSortingEnabled(false);
        myTable->horizontalHeader()->setCascadingSectionResizes(true);
        myTable->horizontalHeader()->setDefaultSectionSize(117);
        myTable->horizontalHeader()->setStretchLastSection(true);
        myTable->verticalHeader()->setVisible(false);

        rightLayout->addWidget(myTable);

        opdaterStatus = new QPushButton(centralWidget);
        opdaterStatus->setObjectName(QStringLiteral("opdaterStatus"));

        rightLayout->addWidget(opdaterStatus);


        horizontalLayout->addLayout(rightLayout);

        horizontalSpacer_3 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 523, 21));
        menuHomeaumation = new QMenu(menuBar);
        menuHomeaumation->setObjectName(QStringLiteral("menuHomeaumation"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuHomeaumation->menuAction());
        menuHomeaumation->addAction(actionLuk);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionLuk->setText(QApplication::translate("MainWindow", "Luk", 0));
        TilfojEnhed->setText(QApplication::translate("MainWindow", "      Tilf\303\270j Enhed     ", 0));
        RedigerEnhed->setText(QApplication::translate("MainWindow", "    Rediger Enhed  ", 0));
        RedigerTidsplan->setText(QApplication::translate("MainWindow", "  Rediger Tidsplan ", 0));
        FjernEnhed->setText(QApplication::translate("MainWindow", "      Fjern enhed    ", 0));
        QTableWidgetItem *___qtablewidgetitem = myTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "ID", 0));
        QTableWidgetItem *___qtablewidgetitem1 = myTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Rum", 0));
        QTableWidgetItem *___qtablewidgetitem2 = myTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "Status", 0));
        opdaterStatus->setText(QApplication::translate("MainWindow", "Opdater Status", 0));
        menuHomeaumation->setTitle(QApplication::translate("MainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
