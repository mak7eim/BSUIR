#include "dialognumin.h"
#include "ui_dialognumin.h"

DialogNumIn::DialogNumIn(QWidget* parent)
    : QDialog(parent), ui(new Ui::DialogNumIn) {
    ui->setupUi(this);
}

DialogNumIn::~DialogNumIn() {
    delete ui;
}

void DialogNumIn::on_lineEdit_editingFinished() {
    bool is_Num;
    QString in = ui->lineEdit->text();

    int num = in.toInt(&is_Num);


    if (is_Num) {
        this->chosen_number = num;
    } else {
        chosen_number = 0;
    }
}


int DialogNumIn::get_value() {
    return this->chosen_number;
};
