#include "mainwindow.h"
#include <QRegularExpression>
#include <QStringList>
#include <QVector>
#include <algorithm>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
    ui_->setupUi(this);
    connect(ui_->processButton, &QPushButton::clicked, this,
            &MainWindow::processSequence);
    setWindowTitle("Медиана");
}

MainWindow::~MainWindow() {
    delete ui_;
}

void MainWindow::processSequence() {
    QString input = ui_->inputLineEdit->text().trimmed();
    if (input.isEmpty()) {
        ui_->outputTextEdit->setText("Ошибка ввода");
        return;
    }

    QStringList numbers =
        input.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    QVector<double> a;
    bool valid = true;


    for (const QString& num : numbers) {
        bool ok;
        double value = num.toDouble(&ok);
        if (!ok) {
            valid = false;
            break;
        }
        a.append(value);
    }

    if (!valid || a.isEmpty()) {
        ui_->outputTextEdit->setText("Ошибка ввода.");
        return;
    }

    QVector<double> b;

    for (int i = 0; i < a.size(); i += 3) {
        if (i + 2 < a.size()) {
            QVector<double> triplet = {a[i], a[i + 1], a[i + 2]};
            std::sort(triplet.begin(), triplet.end());
            b.append(triplet[1]);
        } else if (i + 1 < a.size()) {
            b.append((a[i] + a[i + 1]) / two_);
        } else {
            b.append(a[i]);
        }
    }

    QString result;
    for (int i = 0; i < b.size(); ++i) {
        result += QString::number(b[i]);
        if (i < b.size() - 1) {
            result += ", ";
        }
    }

    ui_->outputTextEdit->setText(result);
}
