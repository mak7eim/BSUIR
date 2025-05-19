#include "mainwindow.h"
#include "circle.h"
#include "figure.h"
#include "hexagon.h"
#include "rectangle.h"
#include "romb.h"
#include "square.h"
#include "star5.h"
#include "star6.h"
#include "star8.h"
#include "trapezoid.h"
#include "triangle.h"
#include "ui_mainwindow.h"

void MainWindow::PrintInfo() {
    ui_->area->setText(QString::number(currentItem_->area()));
    ui_->perimetr->setText(QString::number(currentItem_->perimeter()));
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
    ui_->setupUi(this);

    scene_ = new QGraphicsScene();
    timer_ = new QTimer();

    ui_->graphicsView->setScene(scene_);
}

MainWindow::~MainWindow() {
    delete ui_;
    delete scene_;
    delete timer_;
}

void MainWindow::on_Create_Circle_clicked() {
    scene_->clear();
    currentItem_ = new Circle();
    PrintInfo();
    scene_->addItem(currentItem_);
}

void MainWindow::on_Create_Triangle_clicked() {
    scene_->clear();
    currentItem_ = new Triangle();
    PrintInfo();
    scene_->addItem(currentItem_);
}

void MainWindow::on_Create_Rectangle_clicked() {
    scene_->clear();
    currentItem_ = new rectangle();
    PrintInfo();
    scene_->addItem(currentItem_);
}

void MainWindow::on_Create_Romb_clicked() {
    scene_->clear();
    currentItem_ = new Romb();
    PrintInfo();
    scene_->addItem(currentItem_);
}

void MainWindow::on_Create_Hexagon_clicked() {
    scene_->clear();
    currentItem_ = new Hexagon();
    PrintInfo();
    scene_->addItem(currentItem_);
}

void MainWindow::on_Create_Trapezoid_clicked() {
    scene_->clear();
    currentItem_ = new Trapezoid();
    PrintInfo();
    scene_->addItem(currentItem_);
}

void MainWindow::on_Create_Square_clicked() {
    scene_->clear();
    currentItem_ = new Square();
    PrintInfo();
    scene_->addItem(currentItem_);
}

void MainWindow::on_Create_Star_5_clicked() {
    scene_->clear();
    currentItem_ = new Star5();
    PrintInfo();
    scene_->addItem(currentItem_);
}

void MainWindow::on_Create_Star_6_clicked() {
    scene_->clear();
    currentItem_ = new Star6();
    PrintInfo();
    scene_->addItem(currentItem_);
}

void MainWindow::on_Create_Star_8_clicked() {
    scene_->clear();
    currentItem_ = new Star8();
    PrintInfo();
    scene_->addItem(currentItem_);
}

void MainWindow::on_Rotate_Right_pressed() {


    if (!currentItem_) {
        return;
    }
    connect(timer_, SIGNAL(timeout()), this, SLOT(rotate_right_slot()));
    timer_->start(10);
}

void MainWindow::on_Rotate_Right_released() {


    if (!currentItem_) {
        return;
    }
    disconnect(timer_, SIGNAL(timeout()), this, SLOT(rotate_right_slot()));
    timer_->stop();
}

void MainWindow::on_Rotate_Left_pressed() {


    if (!currentItem_) {
        return;
    }
    connect(timer_, SIGNAL(timeout()), this, SLOT(rotate_left_slot()));
    timer_->start(10);
}

void MainWindow::on_Rotate_Left_released() {


    if (!currentItem_) {
        return;
    }
    disconnect(timer_, SIGNAL(timeout()), this, SLOT(rotate_left_slot()));
    timer_->stop();
}

void MainWindow::on_Move_UP_pressed() {


    if (!currentItem_) {
        return;
    }
    connect(timer_, SIGNAL(timeout()), this, SLOT(move_up_slot()));
    timer_->start(10);
}

void MainWindow::on_Move_UP_released() {


    if (!currentItem_) {
        return;
    }
    disconnect(timer_, SIGNAL(timeout()), this, SLOT(move_up_slot()));
    timer_->stop();
}

void MainWindow::on_Move_DN_pressed() {


    if (!currentItem_) {
        return;
    }
    connect(timer_, SIGNAL(timeout()), this, SLOT(move_down_slot()));
    timer_->start(10);
}

void MainWindow::on_Move_DN_released() {


    if (!currentItem_) {
        return;
    }
    disconnect(timer_, SIGNAL(timeout()), this, SLOT(move_down_slot()));
    timer_->stop();
}

void MainWindow::on_Move_LF_pressed() {


    if (!currentItem_) {
        return;
    }
    connect(timer_, SIGNAL(timeout()), this, SLOT(move_left_slot()));
    timer_->start(10);
}

void MainWindow::on_Move_LF_released() {


    if (!currentItem_) {
        return;
    }

    disconnect(timer_, SIGNAL(timeout()), this, SLOT(move_left_slot()));
    timer_->stop();
}

void MainWindow::on_Move_RG_pressed() {


    if (!currentItem_) {
        return;
    }
    connect(timer_, SIGNAL(timeout()), this, SLOT(move_right_slot()));
    timer_->start(10);
}

void MainWindow::on_Move_RG_released() {


    if (!currentItem_) {
        return;
    }
    disconnect(timer_, SIGNAL(timeout()), this, SLOT(move_right_slot()));
    timer_->stop();
}

void MainWindow::rotate_right_slot() {
    currentItem_->rotate_right();
}

void MainWindow::rotate_left_slot() {
    currentItem_->rotate_left();
}

void MainWindow::SetValue() {
    ui_->area->setText(QString::number(currentItem_->area()));
    ui_->perimetr->setText(QString::number(currentItem_->perimeter()));
}

void MainWindow::size_slot() {
    SetValue();
    currentItem_->getSize();
}

void MainWindow::size_plus_slot() {
    update();
    scale_ += 0.02;
    auto* p = new QPainter(this);
    p->setPen(Qt::black);
    p->end();
}

void MainWindow::size_minus_slot() {
    update();
    scale_ -= 0.02;

    auto* p = new QPainter(this);
    p->setPen(Qt::black);
    p->end();
}

void MainWindow::on_Size_UP_pressed() {


    if (!currentItem_) {
        return;
    }
    currentItem_->setItem(true);
    connect(timer_, SIGNAL(timeout()), this, SLOT(size_slot()));
    timer_->start(10);
}

void MainWindow::on_Size_UP_released() {


    if (!currentItem_) {
        return;
    }
    timer_->stop();
    disconnect(timer_, SIGNAL(timeout()), this, SLOT(size_slot()));
}

void MainWindow::on_Size_DOWN_pressed() {


    if (!currentItem_) {
        return;
    }
    currentItem_->setItem(false);
    connect(timer_, SIGNAL(timeout()), this, SLOT(size_slot()));
    timer_->start(10);
}

void MainWindow::on_Size_DOWN_released() {


    if (!currentItem_) {
        return;
    }
    timer_->stop();
    disconnect(timer_, SIGNAL(timeout()), this, SLOT(size_slot()));
}

void MainWindow::move_up_slot() {
    SetValue();
    currentItem_->move_up();
}

void MainWindow::move_down_slot() {
    SetValue();
    currentItem_->move_down();
}

void MainWindow::move_left_slot() {
    currentItem_->move_left();
}

void MainWindow::move_right_slot() {
    currentItem_->move_right();
}
