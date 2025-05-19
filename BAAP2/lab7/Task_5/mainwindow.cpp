#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::update_table(){
    ui->tableWidget->setColumnCount(deq.size());
    ui->tableWidget->setRowCount(1);
    for(int i = 0 ; i < deq.size(); ++i){
        QTableWidgetItem * itm = new QTableWidgetItem(QString::number(deq[i]));
        ui->tableWidget->setItem(0, i,itm);
    }
}


void MainWindow::on_pop_backbutton_clicked()
{
    deq.pop_back();
    update_table();
}


void MainWindow::on_pop_frontbutton_clicked()
{
    deq.pop_front();
    update_table();
}


void MainWindow::on_push_frontbutton_clicked()
{
    int i = ui->push_frontspin->value();
    deq.push_front(i);
    update_table();
}


void MainWindow::on_push_backbutton_clicked()
{
    deq.push_back(ui->push_backspin->value());
    update_table();
}

