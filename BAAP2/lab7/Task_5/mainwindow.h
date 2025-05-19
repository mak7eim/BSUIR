#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "My_deque.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    My_deque<int> deq;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void update_table();

private slots:
    void on_pop_backbutton_clicked();

    void on_pop_frontbutton_clicked();

    void on_push_frontbutton_clicked();

    void on_push_backbutton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
