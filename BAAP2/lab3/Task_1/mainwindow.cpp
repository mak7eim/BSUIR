#include "mainwindow.h"
#include <QString>
#include <cmath>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
    ui_->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui_;
}


QString intToBinary(long long num, QString result = "") {
    if (num == 0 && result.isEmpty()) {
        return "0";
    }
    if (num == 0) {
        return result;
    }
    result = QString::number(num % 2) + result;
    return intToBinary(num / 2, result);
}


QString fractionalToBinary(double num, int precision, QString result = "") {

    if (precision == 0 || num <= 0) {
        return result;
    }
    num *= 2;
    int bit = floor(num);
    result += QString::number(bit);
    return fractionalToBinary(num - bit, precision - 1, result);
}


QString toIEEE754(double number) {
    if (std::isnan(number)) {
        return "NaN";
    }
    if (std::isinf(number)) {
        return number < 0 ? "-Inf" : "+Inf";
    }
    if (number == 0.0) {
        return number < 0 ? "-0" : "0";
    }

    QString sign = number < 0 ? "1" : "0";
    double abs_number = fabs(number);

    int exponent = floor(log2(abs_number));
    double mantissa = abs_number / pow(2, exponent);

    mantissa -= 1.0;
    const int bias = 1023;


    int biased_exponent = exponent + bias;


    const int bitexp = 11;

    QString exponent_binary = intToBinary(biased_exponent);
    while (exponent_binary.length() < bitexp) {
        exponent_binary = "0" + exponent_binary;
    }
    const int bitman = 52;


    QString mantissa_binary = fractionalToBinary(mantissa, bitman);
    while (mantissa_binary.length() < bitman) {
        mantissa_binary += "0";
    }

    return sign + " " + exponent_binary + " " + mantissa_binary;
}

void MainWindow::on_preobr_button_clicked() {
    QString num_str = ui_->lineEdit->text();
    bool ok;
    double number = num_str.toDouble(&ok);
    if (!ok) {
        ui_->textEdit->setText("Ошибка ввода");
        return;
    }
    QString result;
    if (number - (long long)number == 0 && number >= 0) {
        result = intToBinary(number);
    } else {
        result = toIEEE754(number);
    }
    ui_->textEdit->setText(result);
}
