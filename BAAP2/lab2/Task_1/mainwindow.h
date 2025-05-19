#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QRegularExpression>
#include "QEvent"
#include "date.h"

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
    void on_open_file_button_clicked();

    void on_push_button_birthday_date_clicked();

    void on_push_button_add_date_clicked();

    void on_push_button_edit_clicked();


   private:
    Ui::MainWindow* ui_;
    QVector<Date> dates_;
    void readTextFile();
    bool checkDateLine(QString date);
    void addDateToVector(QString date);
    QString filePath_ = "";
    QFile file_;
    QDate currentDate_;
    QString birthdayDate_ = "01.01.0001";
    bool isBirthdayShow_ = false;
    void changeEvent(QEvent* e) override;
    void update();
    const int date_string_length_ = 10;
    const int year_part_start_ = 6;
    const int year_part_end_ = 9;
    const int yearmonth_ = 12;
    const int dateline_ = 10;
    const int tablenum5_ = 5, tablenum6_ = 6, tablenum7_ = 7;
    const int vesyear_ = 29;
};
#endif	// MAINWINDOW_H
