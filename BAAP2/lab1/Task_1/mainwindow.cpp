#include "mainwindow.h"
#include "dumptruck.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
    ui_->setupUi(this);

    connect(ui_->button1, &QPushButton::clicked, this, &MainWindow::slotUp);
    connect(ui_->button2, &QPushButton::clicked, this, &MainWindow::slotDown);
    connect(timer_, &QTimer::timeout, this, &MainWindow::updatePosition);
    setMinimumSize(800, 500);
    setMaximumSize(800, 500);
}
MainWindow::~MainWindow() {
    delete ui_;
    delete timer_;
}

void MainWindow::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    dump_truck->drawSam(&painter);
}
void MainWindow::slotUp() {
    movingUp_ = true;
    timer_->start(50);
}

void MainWindow::slotDown() {
    movingUp_ = false;
    timer_->start(50);
}

void MainWindow::updatePosition() {


    if (movingUp_) {
        dump_truck->Up();
    } else {
        dump_truck->Down();
    }
    repaint();
}
