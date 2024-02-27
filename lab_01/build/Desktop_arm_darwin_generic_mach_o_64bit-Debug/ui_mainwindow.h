/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_3;
    QToolButton *showSolutionButton;
    QToolButton *showTaskButton;
    QSpacerItem *horizontalSpacer;
    QToolButton *showAboutButton;
    QToolButton *quitButton;
    QMenuBar *menubar;
    QMenu *menumain;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(422, 435);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(3);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(100, 100, 100, 100);
        showSolutionButton = new QToolButton(centralwidget);
        showSolutionButton->setObjectName("showSolutionButton");
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(showSolutionButton->sizePolicy().hasHeightForWidth());
        showSolutionButton->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(18);
        showSolutionButton->setFont(font);

        verticalLayout_3->addWidget(showSolutionButton);

        showTaskButton = new QToolButton(centralwidget);
        showTaskButton->setObjectName("showTaskButton");
        sizePolicy.setHeightForWidth(showTaskButton->sizePolicy().hasHeightForWidth());
        showTaskButton->setSizePolicy(sizePolicy);
        showTaskButton->setFont(font);

        verticalLayout_3->addWidget(showTaskButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_3->addItem(horizontalSpacer);

        showAboutButton = new QToolButton(centralwidget);
        showAboutButton->setObjectName("showAboutButton");
        sizePolicy.setHeightForWidth(showAboutButton->sizePolicy().hasHeightForWidth());
        showAboutButton->setSizePolicy(sizePolicy);
        showAboutButton->setFont(font);

        verticalLayout_3->addWidget(showAboutButton);

        quitButton = new QToolButton(centralwidget);
        quitButton->setObjectName("quitButton");
        sizePolicy.setHeightForWidth(quitButton->sizePolicy().hasHeightForWidth());
        quitButton->setSizePolicy(sizePolicy);
        quitButton->setFont(font);

        verticalLayout_3->addWidget(quitButton);


        gridLayout->addLayout(verticalLayout_3, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 422, 24));
        menumain = new QMenu(menubar);
        menumain->setObjectName("menumain");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menumain->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Menu", nullptr));
        showSolutionButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\320\271\321\202\320\270 \320\272 \321\200\320\265\321\210\320\265\320\275\320\270\321\216", nullptr));
        showTaskButton->setText(QCoreApplication::translate("MainWindow", "\320\243\321\201\320\273\320\276\320\262\320\270\320\265 \320\267\320\260\320\264\320\260\321\207\320\270", nullptr));
        showAboutButton->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261 \320\260\320\262\321\202\320\276\321\200\320\265", nullptr));
        quitButton->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\271\321\202\320\270", nullptr));
        menumain->setTitle(QCoreApplication::translate("MainWindow", "main", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
