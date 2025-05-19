#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAbstractAnimation>
#include <QEasingCurve>
#include <QGraphicsScene>
#include <QInputDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QRandomGenerator>
#include <QThread>
#include <QTimer>
#include <QVBoxLayout>
#include "colomrect.h"

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
    void on_pushButton_3_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_clicked();

    void on_spinBox_2_valueChanged(int arg1);

    void update_visualization(int left, int right, int pivot, int current,
                              const QVector<int>& partitions);

    void on_comboBox_activated(int index);

    void on_pushButton_4_clicked();

   private:
    Ui::MainWindow* ui;
    QGraphicsScene* scene;
    void create_coloms();

   private:
    QVector<ColomRect*> coloms;

   public:
    int colom_count = 20;
    int delay = 50;
    int isActive = 0;

   public:
    void quick_sort(QVector<ColomRect*>& mass, int low, int high);
    int partition(QVector<ColomRect*>& mass, int low, int high);

    void heap_sort(QVector<ColomRect*>& mass);
    void heapify(QVector<ColomRect*>& mass, int n, int i);

    void merge(QVector<ColomRect*>& mass, int left, int mid, int right);
    void merge_sort(QVector<ColomRect*>& mass, int left, int right);

    void update_positions();
    void animate_column_to(ColomRect* col, const QPointF& target);
    void interpolation_sort(QVector<ColomRect*>& arr);
    void insertion_sort_bucket(QVector<ColomRect*>& bucket);
    void update_visualization_for_bucket(const QVector<ColomRect*>& bucket,
                                         int current);
};

#endif	// MAINWINDOW_H
