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
    void on_preobr_button_clicked();

   private:
    Ui::MainWindow* ui_;
    QString BinaryCode(long long num, QString result = "");
    QString FractionToBinary(double num, int precision);
    QString ToIEEE754(double num);
};

#endif	// MAINWINDOW_H
