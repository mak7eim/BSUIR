#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMainWindow>
#include <QString>
#include <QThread>
#include "item.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

   private slots:
    void on_startB_clicked();
    void on_numSB_valueChanged(int arg1);

   private:
    QVector<Item*> items;
    QGraphicsScene* scene;
    Ui::MainWindow* ui;
    void hanoi(int quantity, const QString& from, const QString& to,
               const QString& buf_peg);
    int numA;
    int numB;
    int numC;
    int speed;
    int clickscounter = 0;
    void numDec(QString from);
};
#endif	// MAINWINDOW_H
