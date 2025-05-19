#include "task.h"

Task::Task() {};

Task::Task(const QString& executor, const QString& project, const QString& task,
           const QDate& startDate, const QDate& endDate) {
    executor_ = executor;
    project_ = project;
    task_ = task;
    startDate_ = startDate;
    endDate_ = endDate;
}

QString Task::getExecutor() const {
    return executor_;
}

QString Task::getProject() const {
    return project_;
}

QString Task::getTask() const {
    return task_;
}

QDate Task::getStartDate() const {
    return startDate_;
}

QDate Task::getEndDate() const {
    return endDate_;
}

void Task::setExecutor(const QString& executor) {
    this->executor_ = executor;
}

void Task::setProject(const QString& project) {
    this->project_ = project;
}

void Task::setTask(const QString& task) {
    this->task_ = task;
}

void Task::setStartDate(const QDate& startDate) {
    this->startDate_ = startDate;
}

void Task::setEndDate(const QDate& endDate) {
    this->endDate_ = endDate;
}
