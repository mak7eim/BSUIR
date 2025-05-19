#ifndef STRUCTINPUTDIALOG_H
#define STRUCTINPUTDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "wristWatch.h"

namespace Ui {
class StructInputDialog;
}

class StructInputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StructInputDialog(QWidget*, WristWatch*);
    ~StructInputDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::StructInputDialog *ui;
    WristWatch* w;
    WristWatch input;
};

#endif // STRUCTINPUTDIALOG_H
