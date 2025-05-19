#ifndef TASK_H
#define TASK_H

#include <QDate>
#include <QString>

class Task {
   public:
    Task();
    Task(const QString& executor, const QString& project, const QString& task,
         const QDate& startDate, const QDate& endDate);

    QString getExecutor() const;
    QString getProject() const;
    QString getTask() const;
    QDate getStartDate() const;
    QDate getEndDate() const;

    void setExecutor(const QString& executor);
    void setProject(const QString& project);
    void setTask(const QString& task);
    void setStartDate(const QDate& startDate);
    void setEndDate(const QDate& endDate);

   private:
    QString executor_;
    QString project_;
    QString task_;
    QDate startDate_;
    QDate endDate_;
};

#endif	// TASK_H
