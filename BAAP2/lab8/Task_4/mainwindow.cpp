#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mapa.clear();
    mapa.insert(5, "aboba");
    mapa.insert(6,"bebrus");
    update_table();

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::update_table(){
    std::list<Node<int, QString>*> my_list = mapa.get_list();
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(my_list.size());
    int i =0;
    for(auto it = mapa.begin(); it != mapa.end(); ++it){
        qDebug() << it.get_node()->my_pair.first << " " << it.get_node()->my_pair.second;
        QTableWidgetItem * itm = new QTableWidgetItem(QString::number(it.get_node()->my_pair.first));
        ui->tableWidget->setItem(i, 0 , itm);
        QTableWidgetItem * itm2 = new QTableWidgetItem(it.get_node()->my_pair.second);
        ui->tableWidget->setItem(i, 1 , itm2);
        ++i;

    }

}


void MainWindow::on_insertbutton_clicked()
{
    QString val = ui->insertedit->text();
    int key = ui->insertspin->value();
    mapa.insert(key, val);
    update_table();

}


void MainWindow::on_emptybutton_clicked()
{
    ui->textshow->setText(QString::number(mapa.empty()));

}


void MainWindow::on_sizebutton_clicked()
{
    ui->textshow->setText(QString::number(mapa.size()));
}


void MainWindow::on_clearbutton_clicked()
{
    qDebug()<<"clicked";
    mapa.clear();
    update_table();
}


void MainWindow::on_erasebutton_clicked()
{
    mapa.erase(ui->erasespin->value());
    update_table();

}


void MainWindow::on_atbutton_clicked()
{
    ui->textshow->setText(mapa.at(ui->spinat->value()));
}

