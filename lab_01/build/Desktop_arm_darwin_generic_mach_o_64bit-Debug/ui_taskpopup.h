/********************************************************************************
** Form generated from reading UI file 'taskpopup.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKPOPUP_H
#define UI_TASKPOPUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TaskPopup
{
public:
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QPushButton *closeButton;

    void setupUi(QDialog *TaskPopup)
    {
        if (TaskPopup->objectName().isEmpty())
            TaskPopup->setObjectName("TaskPopup");
        TaskPopup->resize(400, 300);
        gridLayout_2 = new QGridLayout(TaskPopup);
        gridLayout_2->setObjectName("gridLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(TaskPopup);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        closeButton = new QPushButton(TaskPopup);
        closeButton->setObjectName("closeButton");
        QFont font;
        font.setPointSize(13);
        closeButton->setFont(font);

        verticalLayout->addWidget(closeButton);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(TaskPopup);

        QMetaObject::connectSlotsByName(TaskPopup);
    } // setupUi

    void retranslateUi(QDialog *TaskPopup)
    {
        TaskPopup->setWindowTitle(QCoreApplication::translate("TaskPopup", "Dialog", nullptr));
        label->setText(QString());
        closeButton->setText(QCoreApplication::translate("TaskPopup", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TaskPopup: public Ui_TaskPopup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASKPOPUP_H
