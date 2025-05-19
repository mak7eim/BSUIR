#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Map.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Map<int, QString> mapa;
    void update_table();
private slots:
    void on_insertbutton_clicked();

    void on_emptybutton_clicked();

    void on_sizebutton_clicked();

    void on_clearbutton_clicked();

    void on_erasebutton_clicked();

    void on_atbutton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
