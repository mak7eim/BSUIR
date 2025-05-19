#include "taskmanager.h"
#include <QDate>
#include <QTextStream>


void TaskManager::addTask(const Task& task) {
    tasks_.append(task);
}

void TaskManager::removeTask(int index) {
    if (index >= 0 && index < tasks_.size()) {
        tasks_.removeAt(index);
    }
}

void TaskManager::editTask(int index, const Task& task) {
    if (index >= 0 && index < tasks_.size()) {
        tasks_[index] = task;
    }
}

void TaskManager::sortTasksByEndDate() {
    std::sort(tasks_.begin(), tasks_.end(), [](const Task& a, const Task& b) {
        return a.getEndDate() < b.getEndDate();
    });
}

QVector<Task> TaskManager::getTasks() const {
    return tasks_;
}

void TaskManager::loadFromFile(const QString& filename) {
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        tasks_.clear();
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(";");
            if (parts.size() == partssize_) {
                Task task(parts[0], parts[1], parts[2],
                          QDate::fromString(parts[3], "dd.MM.yyyy"),
                          QDate::fromString(parts[4], "dd.MM.yyyy"));
                tasks_.append(task);
            }
        }
        file.close();
    }
}

void TaskManager::saveToFile(const QString& filename) {
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);


        for (const Task& task : tasks_) {
            out << task.getExecutor() << ";" << task.getProject() << ";"
                << task.getTask() << ";"
                << task.getStartDate().toString("dd.MM.yyyy") << ";"
                << task.getEndDate().toString("dd.MM.yyyy") << "\n";
        }
        file.close();
    }
}

QVector<Task> TaskManager::getTasksByExecutor(const QString& executor,
                                              const QDate& date) const {
    QVector<Task> result;


    for (const Task& task : tasks_) {
        if (task.getExecutor() == executor && task.getStartDate() <= date &&
            task.getEndDate() >= date) {
            result.append(task);
        }
    }
    return result;
}

QVector<QPair<QString, int>> TaskManager::getTotalWorkTimeByExecutor() const {
    QMap<QString, int> work_time_map;
    QDate current_date = QDate::currentDate();
    QDate last_month_date = current_date.addMonths(-1);


    for (const Task& task : tasks_) {
        if (task.getStartDate() >= last_month_date &&
            task.getEndDate() <= current_date) {
            int days = task.getStartDate().daysTo(task.getEndDate());
            work_time_map[task.getExecutor()] += days;
        }
    }

    QVector<QPair<QString, int>> result;
    for (auto it = work_time_map.begin(); it != work_time_map.end(); ++it) {
        result.append(qMakePair(it.key(), it.value()));
    }
    return result;
}
