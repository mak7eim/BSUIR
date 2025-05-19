#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "figure.h"

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

   public slots:
    void SetValue();

    void on_Create_Circle_clicked();

    void on_Create_Triangle_clicked();

    void on_Rotate_Right_pressed();

    void on_Rotate_Right_released();

    void rotate_right_slot();

    void rotate_left_slot();

    void move_up_slot();

    void move_down_slot();

    void move_left_slot();

    void move_right_slot();

    void size_slot();

    void size_plus_slot();

    void size_minus_slot();

    void on_Rotate_Left_pressed();

    void on_Rotate_Left_released();

    void on_Create_Star_5_clicked();

    void on_Create_Star_6_clicked();

    void on_Create_Star_8_clicked();

    void on_Create_Rectangle_clicked();

    void on_Create_Romb_clicked();

    void on_Create_Hexagon_clicked();

    void on_Create_Square_clicked();

    void on_Create_Trapezoid_clicked();

    void on_Size_UP_pressed();

    void on_Size_UP_released();

    void on_Size_DOWN_pressed();

    void on_Size_DOWN_released();

    void on_Move_UP_pressed();

    void on_Move_UP_released();

    void on_Move_DN_pressed();

    void on_Move_DN_released();

    void on_Move_LF_pressed();

    void on_Move_LF_released();

    void on_Move_RG_pressed();

    void on_Move_RG_released();


   private:
    QGraphicsScene* scene_;
    Ui::MainWindow* ui_;
    Figure* currentItem_ = nullptr;
    QTimer* timer_;
    bool flag_;
    bool check_;
    float scale_ = 1.0;
    void PrintInfo();
};
#endif	// MAINWINDOW_H
