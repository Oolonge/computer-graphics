/********************************************************************************
** Form generated from reading UI file 'solution1.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOLUTION1_H
#define UI_SOLUTION1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_solution1
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *sizeInput;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QGraphicsView *graphicsView;
    QRadioButton *showCoordinatesRadio;
    QTableView *pointsView;

    void setupUi(QDialog *solution1)
    {
        if (solution1->objectName().isEmpty())
            solution1->setObjectName("solution1");
        solution1->resize(819, 655);
        gridLayoutWidget = new QWidget(solution1);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(40, 30, 740, 601));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        verticalSpacer = new QSpacerItem(50, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(gridLayoutWidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        sizeInput = new QLineEdit(gridLayoutWidget);
        sizeInput->setObjectName("sizeInput");

        horizontalLayout->addWidget(sizeInput);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName("label_2");

        horizontalLayout->addWidget(label_2);

        horizontalSpacer = new QSpacerItem(350, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 1);

        graphicsView = new QGraphicsView(gridLayoutWidget);
        graphicsView->setObjectName("graphicsView");
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy);

        gridLayout->addWidget(graphicsView, 0, 0, 2, 1);

        showCoordinatesRadio = new QRadioButton(gridLayoutWidget);
        showCoordinatesRadio->setObjectName("showCoordinatesRadio");
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(showCoordinatesRadio->sizePolicy().hasHeightForWidth());
        showCoordinatesRadio->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(showCoordinatesRadio, 0, 2, 1, 1);

        pointsView = new QTableView(gridLayoutWidget);
        pointsView->setObjectName("pointsView");
        pointsView->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Ignored, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pointsView->sizePolicy().hasHeightForWidth());
        pointsView->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(pointsView, 1, 2, 1, 1);


        retranslateUi(solution1);

        QMetaObject::connectSlotsByName(solution1);
    } // setupUi

    void retranslateUi(QDialog *solution1)
    {
        solution1->setWindowTitle(QCoreApplication::translate("solution1", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("solution1", "\320\234\320\260\321\201\321\210\321\202\320\260\320\261:", nullptr));
        label_2->setText(QCoreApplication::translate("solution1", "%", nullptr));
        showCoordinatesRadio->setText(QCoreApplication::translate("solution1", "\320\232\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\321\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class solution1: public Ui_solution1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOLUTION1_H
