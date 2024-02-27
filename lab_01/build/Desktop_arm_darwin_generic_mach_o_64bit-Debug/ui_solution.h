/********************************************************************************
** Form generated from reading UI file 'solution.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOLUTION_H
#define UI_SOLUTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Solution
{
public:
    QWidget *centralwidget;
    QGraphicsView *graphicsView;
    QRadioButton *showCoordinatesRadio;
    QLabel *sizeLabel;
    QLineEdit *sizeInput;
    QLabel *percentLabel;
    QTableWidget *pointsTable;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Solution)
    {
        if (Solution->objectName().isEmpty())
            Solution->setObjectName("Solution");
        Solution->resize(885, 771);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Solution->sizePolicy().hasHeightForWidth());
        Solution->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(Solution);
        centralwidget->setObjectName("centralwidget");
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setGeometry(QRect(10, 10, 641, 641));
        graphicsView->viewport()->setProperty("cursor", QVariant(QCursor(Qt::WaitCursor)));
        graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
        graphicsView->setResizeAnchor(QGraphicsView::AnchorUnderMouse);
        showCoordinatesRadio = new QRadioButton(centralwidget);
        showCoordinatesRadio->setObjectName("showCoordinatesRadio");
        showCoordinatesRadio->setEnabled(true);
        showCoordinatesRadio->setGeometry(QRect(670, 50, 121, 31));
        sizeLabel = new QLabel(centralwidget);
        sizeLabel->setObjectName("sizeLabel");
        sizeLabel->setGeometry(QRect(10, 660, 61, 21));
        QFont font;
        font.setPointSize(13);
        sizeLabel->setFont(font);
        sizeLabel->setAlignment(Qt::AlignCenter);
        sizeInput = new QLineEdit(centralwidget);
        sizeInput->setObjectName("sizeInput");
        sizeInput->setGeometry(QRect(80, 660, 113, 21));
        sizeInput->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        percentLabel = new QLabel(centralwidget);
        percentLabel->setObjectName("percentLabel");
        percentLabel->setGeometry(QRect(170, 660, 61, 21));
        percentLabel->setFont(font);
        percentLabel->setAlignment(Qt::AlignCenter);
        pointsTable = new QTableWidget(centralwidget);
        pointsTable->setObjectName("pointsTable");
        pointsTable->setGeometry(QRect(665, 90, 211, 311));
        Solution->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Solution);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 885, 22));
        Solution->setMenuBar(menubar);
        statusbar = new QStatusBar(Solution);
        statusbar->setObjectName("statusbar");
        Solution->setStatusBar(statusbar);

        retranslateUi(Solution);

        QMetaObject::connectSlotsByName(Solution);
    } // setupUi

    void retranslateUi(QMainWindow *Solution)
    {
        Solution->setWindowTitle(QCoreApplication::translate("Solution", "MainWindow", nullptr));
        showCoordinatesRadio->setText(QCoreApplication::translate("Solution", "\320\232\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\321\213", nullptr));
        sizeLabel->setText(QCoreApplication::translate("Solution", "\320\234\320\260\321\201\321\210\321\202\320\260\320\261", nullptr));
        sizeInput->setText(QCoreApplication::translate("Solution", "100", nullptr));
        percentLabel->setText(QCoreApplication::translate("Solution", "%", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Solution: public Ui_Solution {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOLUTION_H
