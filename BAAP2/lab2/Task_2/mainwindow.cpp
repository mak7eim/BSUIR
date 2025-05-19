#include "mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTableWidget>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::updateTaskList() {
    ui->taskTableWidget->setRowCount(0);

    for (const Task& task : taskManager.getTasks()) {
        int row = ui->taskTableWidget->rowCount();
        ui->taskTableWidget->insertRow(row);

        ui->taskTableWidget->setItem(row, 0,
                                     new QTableWidgetItem(task.getExecutor()));
        ui->taskTableWidget->setItem(row, 1,
                                     new QTableWidgetItem(task.getProject()));
        ui->taskTableWidget->setItem(row, 2,
                                     new QTableWidgetItem(task.getTask()));
        ui->taskTableWidget->setItem(
            row, 3,
            new QTableWidgetItem(task.getStartDate().toString("dd.MM.yyyy")));
        ui->taskTableWidget->setItem(
            row, 4,
            new QTableWidgetItem(task.getEndDate().toString("dd.MM.yyyy")));
    }
}

void MainWindow::on_add_task_button_clicked() {
    QString executor = ui->executorLineEdit->text();
    QString project = ui->projectLineEdit->text();
    QString task = ui->taskLineEdit->text();
    QDate start_date = ui->startDateEdit->date();
    QDate end_date = ui->endDateEdit->date();

    if (executor.isEmpty() || project.isEmpty() || task.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Все поля должны быть заполнены!");
        return;
    }

    Task new_task(executor, project, task, start_date, end_date);
    taskManager.addTask(new_task);
    updateTaskList();

    ui->executorLineEdit->clear();
    ui->projectLineEdit->clear();
    ui->taskLineEdit->clear();
}

void MainWindow::on_remove_task_button_clicked() {
    int row = ui->taskTableWidget->currentRow();


    if (row != -1) {
        taskManager.removeTask(row);
        updateTaskList();
    }
}

void MainWindow::on_edit_task_button_clicked() {
    int row = ui->taskTableWidget->currentRow();


    if (row != -1) {
        QString executor = ui->executorLineEdit->text();
        QString project = ui->projectLineEdit->text();
        QString task = ui->taskLineEdit->text();
        QDate star_date = ui->startDateEdit->date();
        QDate end_date = ui->endDateEdit->date();

        Task edited_task(executor, project, task, star_date, end_date);
        taskManager.editTask(row, edited_task);
        updateTaskList();
    }
}

void MainWindow::on_sort_tasks_button_clicked() {
    taskManager.sortTasksByEndDate();
    updateTaskList();
}

void MainWindow::on_load_tasks_button_clicked() {
    QString filename = QFileDialog::getOpenFileName(this, "Открыть файл", "",
                                                    "Текстовые файлы (*.txt)");
    if (!filename.isEmpty()) {
        taskManager.loadFromFile(filename);
        updateTaskList();
    }
}


void MainWindow::on_get_tasks_by_executor_button_clicked() {
    QString executor = ui->executorLineEdit->text();
    QDate today = QDate::currentDate();

    qDebug() << "Исполнитель:" << executor;
    qDebug() << "Текущая дата:" << today.toString("dd.MM.yyyy");

    QVector<Task> tasks = taskManager.getTasksByExecutor(executor, today);
    ui->outputTextEdit->clear();

    if (tasks.isEmpty()) {
        ui->outputTextEdit->append("Задачи за сегодня не найдены.");
    } else {


        for (const Task& task : tasks) {
            ui->outputTextEdit->append(
                "Исполнитель: " + task.getExecutor() + "\n" + "Проект: " +
                task.getProject() + "\n" + "Задание: " + task.getTask() + "\n" +
                "Дата начала: " + task.getStartDate().toString("dd.MM.yyyy") +
                "\n" + "Дата окончания: " +
                task.getEndDate().toString("dd.MM.yyyy") + "\n");
        }
    }
}

void MainWindow::on_get_total_work_time_button_clicked() {
    QVector<QPair<QString, int>> work_time =
        taskManager.getTotalWorkTimeByExecutor();
    ui->outputTextEdit->clear();

    if (work_time.isEmpty()) {
        ui->outputTextEdit->append("Данные за последний месяц отсутствуют.");
    } else {


        for (const auto& pair : work_time) {
            ui->outputTextEdit->append(
                "Исполнитель: " + pair.first + "\n" +
                "Суммарное время: " + QString::number(pair.second) + " дней\n");
        }
    }
}

void MainWindow::on_save_tasks_button_clicked() {
    QString filename = QFileDialog::getSaveFileName(this, "Save File", "",
                                                    "Text Files (*.txt)");
    if (!filename.isEmpty()) {
        taskManager.saveToFile(filename);
    }
}
