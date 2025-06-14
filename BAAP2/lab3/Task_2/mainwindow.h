#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_output_button_clicked();

   private:
    Ui::MainWindow* ui_;

    long double Akkerman(long long n1, long long n2);
};
#endif	// MAINWINDOW_H
