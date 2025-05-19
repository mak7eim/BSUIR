#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <QFile>
#include <QVector>
#include "task.h"

class TaskManager {
   public:
    void addTask(const Task& task);
    void removeTask(int index);
    void editTask(int index, const Task& task);
    void sortTasksByEndDate();
    QVector<Task> getTasks() const;

    void loadFromFile(const QString& filename);
    void saveToFile(const QString& filename);

    QVector<Task> getTasksByExecutor(const QString& executor,
                                     const QDate& date) const;
    QVector<QPair<QString, int>> getTotalWorkTimeByExecutor() const;

   private:
    QVector<Task> tasks_;
    const int partssize_ = 5;
};

#endif	// TASKMANAGER_H
