#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "taskmanager.h"

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
    void on_add_task_button_clicked();
    void on_remove_task_button_clicked();
    void on_edit_task_button_clicked();
    void on_sort_tasks_button_clicked();
    void on_load_tasks_button_clicked();
    void on_save_tasks_button_clicked();
    void on_get_tasks_by_executor_button_clicked();
    void on_get_total_work_time_button_clicked();

   private:
    Ui::MainWindow* ui;
    TaskManager taskManager;
    void updateTaskList();
};

#endif	// MAINWINDOW_H
