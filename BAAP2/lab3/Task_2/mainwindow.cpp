#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
    ui_->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui_;
}

void MainWindow::on_output_button_clicked() {


    QString m = ui_->lineEdit->text();

    bool ok1;
    long long m1 = m.toLongLong(&ok1);

    QString n = ui_->lineEdit_2->text();

    bool ok2;
    long long n1 = n.toLongLong(&ok2);
    if (!ok1 || !ok2) {
        ui_->lineEdit_3->setText("Ошибка ввода!");
        return;
    }

    long long res = Akkerman(m1, n1);

    ui_->lineEdit_3->setText(QString::number(res));
}

long double MainWindow::Akkerman(long long m, long long n) {
    if (m == 0) {
        return n + 1;
    } else if (m > 0 && n == 0) {
        return Akkerman(m - 1, 1);
    } else {
        return Akkerman(m - 1, Akkerman(m, n - 1));
    }
}
