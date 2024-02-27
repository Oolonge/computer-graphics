/********************************************************************************
** Form generated from reading UI file 'aboutpopup.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTPOPUP_H
#define UI_ABOUTPOPUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_aboutpopup
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QPushButton *pushButton;

    void setupUi(QDialog *aboutpopup)
    {
        if (aboutpopup->objectName().isEmpty())
            aboutpopup->setObjectName("aboutpopup");
        aboutpopup->resize(539, 383);
        gridLayout = new QGridLayout(aboutpopup);
        gridLayout->setObjectName("gridLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(aboutpopup);
        label->setObjectName("label");
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        pushButton = new QPushButton(aboutpopup);
        pushButton->setObjectName("pushButton");

        verticalLayout->addWidget(pushButton);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(aboutpopup);
        QObject::connect(pushButton, &QPushButton::clicked, aboutpopup, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(aboutpopup);
    } // setupUi

    void retranslateUi(QDialog *aboutpopup)
    {
        aboutpopup->setWindowTitle(QCoreApplication::translate("aboutpopup", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("aboutpopup", "text", nullptr));
        pushButton->setText(QCoreApplication::translate("aboutpopup", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class aboutpopup: public Ui_aboutpopup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTPOPUP_H
