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
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLUk;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout;
    QPushButton *TilfojEnhed;
    QPushButton *RedigerEnhed;
    QPushButton *RedigerTidsplan;
    QPushButton *FjernEnhed;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_4;
    QTextBrowser *textBrowser;
    QPushButton *OpdaterStatus;
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
        actionLUk = new QAction(MainWindow);
        actionLUk->setObjectName(QStringLiteral("actionLUk"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(50, 10, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        TilfojEnhed = new QPushButton(centralWidget);
        TilfojEnhed->setObjectName(QStringLiteral("TilfojEnhed"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(50);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(TilfojEnhed->sizePolicy().hasHeightForWidth());
        TilfojEnhed->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(TilfojEnhed);

        RedigerEnhed = new QPushButton(centralWidget);
        RedigerEnhed->setObjectName(QStringLiteral("RedigerEnhed"));
        sizePolicy1.setHeightForWidth(RedigerEnhed->sizePolicy().hasHeightForWidth());
        RedigerEnhed->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(RedigerEnhed);

        RedigerTidsplan = new QPushButton(centralWidget);
        RedigerTidsplan->setObjectName(QStringLiteral("RedigerTidsplan"));
        sizePolicy1.setHeightForWidth(RedigerTidsplan->sizePolicy().hasHeightForWidth());
        RedigerTidsplan->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(RedigerTidsplan);

        FjernEnhed = new QPushButton(centralWidget);
        FjernEnhed->setObjectName(QStringLiteral("FjernEnhed"));
        sizePolicy1.setHeightForWidth(FjernEnhed->sizePolicy().hasHeightForWidth());
        FjernEnhed->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(FjernEnhed);


        horizontalLayout->addLayout(verticalLayout);

        horizontalSpacer = new QSpacerItem(50, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        verticalLayout_4->addWidget(textBrowser);

        OpdaterStatus = new QPushButton(centralWidget);
        OpdaterStatus->setObjectName(QStringLiteral("OpdaterStatus"));

        verticalLayout_4->addWidget(OpdaterStatus);


        verticalLayout_3->addLayout(verticalLayout_4);


        horizontalLayout->addLayout(verticalLayout_3);

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
        menuHomeaumation->addAction(actionLUk);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionLUk->setText(QApplication::translate("MainWindow", "LUk", 0));
        TilfojEnhed->setText(QApplication::translate("MainWindow", "      Tilf\303\270j Enhed     ", 0));
        RedigerEnhed->setText(QApplication::translate("MainWindow", "    Rediger Enhed  ", 0));
        RedigerTidsplan->setText(QApplication::translate("MainWindow", "  Rediger Tidsplan ", 0));
        FjernEnhed->setText(QApplication::translate("MainWindow", "      Fjern enhed    ", 0));
        OpdaterStatus->setText(QApplication::translate("MainWindow", "Opdater status", 0));
        menuHomeaumation->setTitle(QApplication::translate("MainWindow", "Homeaumation", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
