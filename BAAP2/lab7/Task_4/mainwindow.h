#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "hashtable.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget* parent = nullptr);
    My_hashtable* t16;
    My_hashtable* t64;
    My_hashtable* t128;
    My_hashtable* t2048;

    ~MainWindow();

   private:
    Ui::MainWindow* ui;
};
#endif	// MAINWINDOW_H
