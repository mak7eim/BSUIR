#include "userinputdialog.h"
#include "ui_userinputdialog.h"
#include <QMessageBox>

UserInputDialog::UserInputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserInputDialog)
{
    ui->setupUi(this);
    ui->lineEdit->setMaxLength(WristWatch::MAX_NAME_SIZE - 1);
    const int timeZoneMin = -12;
    const int timeZoneMax = 14;

    ui->spinBox_2->setRange(timeZoneMin, timeZoneMax);
    ui->spinBox_3->setRange(timeZoneMin, timeZoneMax);
    ui->spinBox_4->setRange(timeZoneMin, timeZoneMax);
    ui->spinBox_5->setRange(timeZoneMin, timeZoneMax);
    ui->spinBox_7->setRange(timeZoneMin, timeZoneMax);
    ui->spinBox_8->setRange(timeZoneMin, timeZoneMax);
}

UserInputDialog::~UserInputDialog()
{
    delete ui;
}

void UserInputDialog::on_buttonBox_accepted()
{
    if (ui->lineEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Поле 'Brand name' не может быть пустым!");
        return;
    }

    if (ui->lineEdit_2->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Поле 'Model' не может быть пустым!");
        return;
    }

    if (ui->lineEdit_2->text().length() > 6) {
        QMessageBox::warning(this, "Ошибка", "Модель может содержать только 1 символ");
        return;
    }

    WristWatch watch;

    QString brand = ui->lineEdit->text();
    int copyLength = qMin(brand.length(), WristWatch::MAX_NAME_SIZE - 1);
    for (int i = 0; i < copyLength; ++i) {
        watch.brandNAme[i] = brand.at(i);
    }
    watch.brandNAme[copyLength] = '\0';

    watch.numberOfDiamond = ui->spinBox->value();
    watch.Model = ui->lineEdit_2->text().at(0);
    watch.price = ui->doubleSpinBox->value();
    watch.isexpensivewristwatch = ui->checkBox->isChecked();

    watch.worldTimeOffsets[0] = ui->spinBox_2->value();
    watch.worldTimeOffsets[1] = ui->spinBox_3->value();
    watch.worldTimeOffsets[2] = ui->spinBox_4->value();
    watch.worldTimeOffsets[3] = ui->spinBox_5->value();
    watch.worldTimeOffsets[4] = ui->spinBox_7->value();
    watch.worldTimeOffsets[5] = ui->spinBox_8->value();

    emit inputInit(watch);
    accept();
}

void UserInputDialog::on_spinBox_valueChanged(int value)
{
    Q_UNUSED(value);
}
