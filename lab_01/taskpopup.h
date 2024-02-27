#ifndef TASKPOPUP_H
#define TASKPOPUP_H

#include <QDialog>

namespace Ui {
class TaskPopup;
}

class TaskPopup : public QDialog
{
    Q_OBJECT

public:
    explicit TaskPopup(QWidget *parent = nullptr);
    ~TaskPopup();

public slots:
    void onCloseButtonClicked();

private:
    Ui::TaskPopup *ui;
};

#endif // TASKPOPUP_H
