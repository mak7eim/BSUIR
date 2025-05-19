#include "StructInputDialog.h"
#include "ui_structinputdialog.h"

StructInputDialog::StructInputDialog(QWidget *parent, WristWatch* ref) :
    QDialog(parent), ui(new Ui::StructInputDialog),
    w(ref)
{
    ui->setupUi(this);
    ui->lineEdit->setMaxLength(WristWatch::MAX_NAME_SIZE - 1);
}

StructInputDialog::~StructInputDialog()
{
    delete ui;
}

void StructInputDialog::on_buttonBox_accepted()
{
    QString name = ui->lineEdit->text();
    for (int i = 0; i < name.length(); ++i)
    {
        w->brandName[i] = name.at(i);
    }
    w->brandName[name.length()] = QChar('\0');

    w->numberOfDiamond = ui->spinBox->value();
    w->Model = ui->lineEdit_2->text().isEmpty() ? QChar(' ') : ui->lineEdit_2->text().at(0);
    w->price = ui->doubleSpinBox->value();
    w->isexpensivewristwatch = ui->checkBox->isChecked();

    w->worldTimeOffsets[0] = ui->spinBox_2->value();
    w->worldTimeOffsets[1] = ui->spinBox_3->value();
    w->worldTimeOffsets[2] = ui->spinBox_4->value();
    w->worldTimeOffsets[3] = ui->spinBox_5->value();
    w->worldTimeOffsets[4] = ui->spinBox_6->value();
    w->worldTimeOffsets[5] = ui->spinBox_7->value();
    close();
}
