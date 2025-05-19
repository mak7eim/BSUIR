#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(ui->graphicsView->geometry());

    QGraphicsRectItem* rect1 = new QGraphicsRectItem(-300, 150, 600, 60);
    rect1->setBrush(Qt::gray);
    QBrush b_brush("#000000");
    QGraphicsRectItem* rect2 = new QGraphicsRectItem(-7.5, -50, 15, 200);
    rect2->setBrush(b_brush);
    QGraphicsRectItem* rect3 = new QGraphicsRectItem(-207.5, -50, 15, 200);
    rect3->setBrush(b_brush);
    QGraphicsRectItem* rect4 = new QGraphicsRectItem(192.5, -50, 15, 200);
    rect4->setBrush(b_brush);
    scene->addItem(rect1);
    scene->addItem(rect2);
    scene->addItem(rect3);
    scene->addItem(rect4);

    ui->numSB->setMaximum(10);
    ui->numSB->setMinimum(3);

    QGraphicsTextItem* l1 = new QGraphicsTextItem();
    QFont font("Arial", 18);
    l1->setPlainText("A");
    l1->setFont(font);
    l1->setPos(-215, 160);
    scene->addItem(l1);

    QGraphicsTextItem* l2 = new QGraphicsTextItem();
    l2->setPlainText("B");
    l2->setFont(font);
    l2->setPos(-11, 160);
    scene->addItem(l2);

    QGraphicsTextItem* l3 = new QGraphicsTextItem();
    l3->setPlainText("C");
    l3->setFont(font);
    l3->setPos(185, 160);
    scene->addItem(l3);
}

void MainWindow::hanoi(int quantity, const QString& from, const QString& to,
                       const QString& buf_peg) {
    if (quantity != 0) {
        hanoi(quantity - 1, from, buf_peg, to);

        ui->output->append(QString::number(items.size() - quantity + 1) + "  " +
                           from + " -> " + to);
        if (to == "A") {
            QEventLoop loop;
            QObject::connect(items[items.size() - quantity], &Item::mAFinished,
                             &loop, &QEventLoop::quit);
            items[items.size() - quantity]->mA(numA, speed);
            loop.exec();
            numA++;
            numDec(from);
        }


        if (to == "B") {
            QEventLoop loop1;
            QObject::connect(items[items.size() - quantity], &Item::mBFinished,
                             &loop1, &QEventLoop::quit);
            items[items.size() - quantity]->mB(numB, speed);
            loop1.exec();
            numB++;
            numDec(from);
        }


        if (to == "C") {
            QEventLoop loop2;
            QObject::connect(items[items.size() - quantity], &Item::mCFinished,
                             &loop2, &QEventLoop::quit);
            items[items.size() - quantity]->mC(numC, speed);
            loop2.exec();
            numC++;
            numDec(from);
        }

        hanoi(quantity - 1, buf_peg, to, from);
    }
}

void MainWindow::numDec(QString from) {
    if (from == "A") {
        numA--;
    }
    if (from == "B") {
        numB--;
    }
    if (from == "C") {
        numC--;
    }
}

MainWindow::~MainWindow() {

    delete ui;
}

void MainWindow::on_startB_clicked() {
    clickscounter += 1;
    int n = ui->numSB->value();
    for (int i = 0; i < items.size(); i++) {
        scene->removeItem(items[i]);
        delete items[i];
    }
    items.clear();
    double h[11]{0, 0, 125, 62.5, 50, 40, 32.5, 30, 25, 22.5, 20};


    for (int i = 0; i < n; i++) {
        Item* iy = new Item(-400, (int)(150 - h[n] * i), (50 + 150 - h[n] * i),
                            h[n], i + 1);
        items.push_back(iy);
        scene->addItem(items[i]);
    }
    ui->output->clear();
    numA = ui->numSB->value();
    numB = 0;
    numC = 0;
    if (clickscounter == 1) {
        hanoi(ui->numSB->value(), "A", "C", "B");
    } else {
        clickscounter = 0;
    }
}

void MainWindow::on_numSB_valueChanged(int arg1) {
    switch (arg1) {
        case 3:
            speed = 10;
            break;
        case 4:
            speed = 8;
            break;
        case 5:
            speed = 5;
            break;
        case 6:
            speed = 3;
            break;
        case 7:
            speed = 3;
            break;
        case 8:
            speed = 2;
            break;
        case 9:
            speed = 2;
            break;
        case 10:
            speed = 1;
            break;
    }

    ui->output->clear();
    int n = ui->numSB->value();
    for (int i = 0; i < items.size(); i++) {
        scene->removeItem(items[i]);
        delete items[i];
    }
    items.clear();
    double h[11]{0, 0, 125, 62.5, 50, 40, 32.5, 30, 25, 22.5, 20};


    for (int i = 0; i < n; i++) {
        Item* iy = new Item(-400, (int)(150 - h[n] * i), (50 + 150 - h[n] * i),
                            h[n], i + 1);
        items.push_back(iy);
        scene->addItem(items[i]);
    }
}
