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
    void on_reverse_button_clicked();

   private:
    Ui::MainWindow* ui_;
    long long Reverse(long long num, long long a = 0);
    const long long ten_ = 10;
};
#endif	// MAINWINDOW_H
