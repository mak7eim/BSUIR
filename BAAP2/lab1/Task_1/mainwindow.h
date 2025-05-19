#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "dumptruck.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    DumpTruck* dump_truck = new DumpTruck;
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

   private slots:
    void slotUp();
    void slotDown();
    void updatePosition();

   protected:
    void paintEvent(QPaintEvent*) override;

   private:
    Ui::MainWindow* ui_;
    QTimer* timer_ = new QTimer;
    bool movingUp_;
};

#endif	// MAINWINDOW_H
