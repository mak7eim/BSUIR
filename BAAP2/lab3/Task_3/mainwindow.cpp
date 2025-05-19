#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
    ui_->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui_;
}

void MainWindow::on_reverse_button_clicked() {
    QString num = ui_->lineEdit->text();


    bool ok;
    unsigned long long num1 = num.toULongLong(&ok);
    if (!ok) {
        ui_->lineEdit_2->setText("Ошибка ввода!");
        return;
    }


    unsigned long long res = Reverse(num1);

    ui_->lineEdit_2->setText(QString::number(res));
}

long long MainWindow::Reverse(long long num, long long a) {
    if (num == 0) {
        return a;
    } else {
        return Reverse(num / ten_, ten_ * a + num % ten_);
    }
}
