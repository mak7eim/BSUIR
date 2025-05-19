#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      scene(new QGraphicsScene(this)) {
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::create_coloms() {
    scene->clear();
    coloms.clear();
    qreal scene_width = ui->graphicsView->width();
    qreal scene_height = ui->graphicsView->height();

    qreal colomn_width = scene_width / colom_count;
    qreal max_colomn_height = scene_height - 20;


    for (size_t i = 0; i < colom_count; ++i) {
        qreal colomh_height = QRandomGenerator::global()->generateDouble() *
                                  (max_colomn_height - 20) +
                              20;
        ColomRect* temp = new ColomRect(colomn_width - 2, colomh_height);
        QPointF target(i * (temp->get_width() + 2),
                       max_colomn_height - colomh_height);
        animate_column_to(temp, target);
        scene->addItem(temp);
        coloms.append(temp);
    }
};

void MainWindow::on_pushButton_3_clicked() {
    create_coloms();
}

void MainWindow::on_spinBox_valueChanged(int arg1) {
    this->colom_count = arg1;
}

void MainWindow::on_pushButton_clicked() {
    switch (isActive) {
        case 0:
            quick_sort(coloms, 0, coloms.size() - 1);
            break;
        case 1:
            heap_sort(coloms);
            break;
        case 2:
            merge_sort(coloms, 0, coloms.size() - 1);
            break;
        case 3:
            interpolation_sort(coloms);
            break;
        default:
            break;
    }
}

void MainWindow::quick_sort(QVector<ColomRect*>& mass, int low, int high) {
    if (low < high) {
        int pi = partition(mass, low, high);
        quick_sort(mass, low, pi - 1);
        quick_sort(mass, pi + 1, high);
    }
}

int MainWindow::partition(QVector<ColomRect*>& mass, int low, int high) {
    qreal pivot = mass[high]->get_hight();
    int i = (low - 1);
    QVector<int> partitions = {low, high};


    for (int j = low; j <= high - 1; j++) {
        update_visualization(low, high, high, j, partitions);
        QThread::msleep(delay);

        if (mass[j]->get_hight() < pivot) {
            i++;
            ColomRect* temp = mass[i];
            mass[i] = mass[j];
            mass[j] = temp;

            update_positions();
            update_visualization(low, high, high, j, partitions);
            QThread::msleep(delay);
        }
    }
    qSwap(mass[i + 1], mass[high]);
    return (i + 1);
};

void MainWindow::update_visualization(int left, int right, int pivot,
                                      int current,
                                      const QVector<int>& partitions) {


    for (ColomRect* column : coloms) {
        column->set_new_state(ColomRect::state::Unsorted);
    }


    for (int i = left; i <= right; i++) {
        coloms[i]->set_new_state(ColomRect::state::ActiveRange);
    }
    if (pivot >= 0 && pivot < coloms.size()) {
        coloms[pivot]->set_new_state(ColomRect::state::Pivot);
    }
    if (current >= 0 && current < coloms.size()) {
        coloms[current]->set_new_state(ColomRect::state::Current);
    }


    for (int p : partitions) {
        if (p >= 0 && p < coloms.size()) {
            coloms[p]->set_new_state(ColomRect::state::Partition);
        }
    }
    scene->update();
    QApplication::processEvents();
}

void MainWindow::on_spinBox_2_valueChanged(int arg1) {
    this->delay = arg1;
}

void MainWindow::update_positions() {
    qreal scene_height = ui->graphicsView->height();
    qreal max_colomn_height = scene_height - 20;

    for (size_t i = 0; i < coloms.size(); ++i) {
        QPointF target(i * (coloms[i]->get_width() + 2),
                       max_colomn_height - coloms[i]->get_hight());
        animate_column_to(coloms[i], target);
    }
};

void MainWindow::heap_sort(QVector<ColomRect*>& mass) {
    int n = mass.size();


    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(mass, n, i);
        update_visualization(i, n - 1, -1, i, {i, 2 * i + 1, 2 * i + 2});
        QThread::msleep(delay / 2);
    }


    for (int i = n - 1; i > 0; i--) {
        qSwap(mass[0], mass[i]);
        update_positions();
        for (int j = i; j < n; j++) {
            mass[j]->set_new_state(ColomRect::state::Sorted);
        }

        update_visualization(0, i - 1, -1, -1, {0});
        QThread::msleep(delay);

        heapify(mass, i, 0);
    }

    mass[0]->set_new_state(ColomRect::state::Sorted);
}

void MainWindow::heapify(QVector<ColomRect*>& mass, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    mass[i]->set_new_state(ColomRect::state::HeapNode);
    if (left < n)
        mass[left]->set_new_state(ColomRect::state::Current);
    if (right < n)
        mass[right]->set_new_state(ColomRect::state::Current);
    scene->update();
    QApplication::processEvents();
    QThread::msleep(delay / 3);

    if (left < n && mass[left]->get_hight() > mass[largest]->get_hight()) {
        largest = left;
    }

    if (right < n && mass[right]->get_hight() > mass[largest]->get_hight()) {
        largest = right;
    }
    if (largest != i) {
        qSwap(mass[i], mass[largest]);
        update_positions();
        update_visualization(0, n - 1, -1, largest, {i, largest});
        QThread::msleep(delay);
        heapify(mass, n, largest);
    }

    mass[i]->set_new_state(ColomRect::state::ActiveRange);
    if (left < n)
        mass[left]->set_new_state(ColomRect::state::ActiveRange);
    if (right < n)
        mass[right]->set_new_state(ColomRect::state::ActiveRange);
}

void MainWindow::merge_sort(QVector<ColomRect*>& mass, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        update_visualization(left, right, mid, -1, {left, right});
        QThread::msleep(delay / 2);

        merge_sort(mass, left, mid);
        merge_sort(mass, mid + 1, right);

        merge(mass, left, mid, right);

        for (int i = left; i <= right; i++) {
            mass[i]->set_new_state(ColomRect::state::Sorted);
        }
        scene->update();
        QApplication::processEvents();
        QThread::msleep(delay / 2);
    }
}

void MainWindow::merge(QVector<ColomRect*>& mass, int left, int mid,
                       int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    QVector<ColomRect*> leftArray(n1), rightArray(n2);


    for (int i = 0; i < n1; i++) {
        leftArray[i] = mass[left + i];
        leftArray[i]->set_new_state(ColomRect::state::Current);
    }


    for (int i = 0; i < n2; i++) {
        rightArray[i] = mass[mid + 1 + i];
        rightArray[i]->set_new_state(ColomRect::state::Partition);
    }

    scene->update();
    QApplication::processEvents();
    QThread::msleep(delay);

    int i = 0, j = 0, k = left;
    qreal scene_height = ui->graphicsView->height();
    qreal max_colomn_height = scene_height - 20;


    while (i < n1 && j < n2) {
        if (leftArray[i]->get_hight() <= rightArray[j]->get_hight()) {
            mass[k] = leftArray[i];
            mass[k]->set_new_state(ColomRect::state::Sorted);
            animate_column_to(
                mass[k], QPointF(k * (mass[k]->get_width() + 2),
                                 max_colomn_height - mass[k]->get_hight()));
            i++;
        } else {
            mass[k] = rightArray[j];
            mass[k]->set_new_state(ColomRect::state::Sorted);
            animate_column_to(
                mass[k], QPointF(k * (mass[k]->get_width() + 2),
                                 max_colomn_height - mass[k]->get_hight()));
            j++;
        }

        scene->update();
        QApplication::processEvents();
        QThread::msleep(delay * 1.2);
        k++;
    }


    while (i < n1) {
        mass[k] = leftArray[i];
        mass[k]->set_new_state(ColomRect::state::Sorted);
        animate_column_to(mass[k],
                          QPointF(k * (mass[k]->get_width() + 2),
                                  max_colomn_height - mass[k]->get_hight()));
        scene->update();
        QApplication::processEvents();
        QThread::msleep(delay * 1.2);
        i++;
        k++;
    }


    while (j < n2) {
        mass[k] = rightArray[j];
        mass[k]->set_new_state(ColomRect::state::Sorted);
        animate_column_to(mass[k],
                          QPointF(k * (mass[k]->get_width() + 2),
                                  max_colomn_height - mass[k]->get_hight()));
        scene->update();
        QApplication::processEvents();
        QThread::msleep(delay * 1.2);
        j++;
        k++;
    }
}

void MainWindow::on_comboBox_activated(int index) {
    this->isActive = index;
}

void MainWindow::animate_column_to(ColomRect* col, const QPointF& target) {
    QPropertyAnimation* anim = new QPropertyAnimation(col, "pos");
    anim->setDuration(delay);
    anim->setEndValue(target);
    anim->setEasingCurve(QEasingCurve::OutCubic);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void MainWindow::interpolation_sort(QVector<ColomRect*>& arr) {
    if (arr.isEmpty())
        return;

    qreal min_val = arr[0]->get_hight();
    qreal max_val = arr[0]->get_hight();


    for (ColomRect* col : arr) {
        min_val = qMin(min_val, col->get_hight());
        max_val = qMax(max_val, col->get_hight());
    }
    if (min_val == max_val) {
        for (ColomRect* col : arr) {
            col->set_new_state(ColomRect::state::Sorted);
        }
        scene->update();
        QApplication::processEvents();
        return;
    }

    int bucket_count = arr.size();
    QVector<QVector<ColomRect*>> buckets(bucket_count);


    for (ColomRect* col : arr) {
        qreal normalized = (col->get_hight() - min_val) / (max_val - min_val);
        int bucket_index =
            qMin(static_cast<int>(normalized * bucket_count), bucket_count - 1);
        buckets[bucket_index].append(col);

        col->set_new_state(ColomRect::state::Current);
        scene->update();
        QApplication::processEvents();
        QThread::msleep(delay / 2);
        col->set_new_state(ColomRect::state::Unsorted);
    }

    int index = 0;


    for (QVector<ColomRect*>& bucket : buckets) {
        insertion_sort_bucket(bucket);

        for (ColomRect* col : bucket) {
            arr[index++] = col;

            col->set_new_state(ColomRect::state::Sorted);
            update_positions();
            scene->update();
            QApplication::processEvents();
            QThread::msleep(delay);
        }
    }
}

void MainWindow::insertion_sort_bucket(QVector<ColomRect*>& bucket) {
    for (int i = 1; i < bucket.size(); ++i) {
        ColomRect* key = bucket[i];
        int j = i - 1;

        key->set_new_state(ColomRect::state::Current);
        scene->update();
        QApplication::processEvents();
        QThread::msleep(delay / 2);

        while (j >= 0 && bucket[j]->get_hight() > key->get_hight()) {
            bucket[j + 1] = bucket[j];
            j--;

            update_visualization_for_bucket(bucket, j + 1);
            QThread::msleep(delay / 2);
        }
        bucket[j + 1] = key;

        update_visualization_for_bucket(bucket, j + 1);
        QThread::msleep(delay);
    }
}

void MainWindow::update_visualization_for_bucket(
    const QVector<ColomRect*>& bucket, int current) {
    for (int i = 0; i < bucket.size(); ++i) {
        if (i == current) {
            bucket[i]->set_new_state(ColomRect::state::Current);
        } else if (i < current) {
            bucket[i]->set_new_state(ColomRect::state::Sorted);
        } else {
            bucket[i]->set_new_state(ColomRect::state::Unsorted);
        }
    }
    scene->update();
    QApplication::processEvents();
}

void MainWindow::on_pushButton_4_clicked() {


    for (size_t i = 0; i < colom_count; i++) {
        coloms[i]->set_new_state(ColomRect::Unsorted);
    }

    scene->update();
    QApplication::processEvents();

    bool ok;
    int value =
        QInputDialog::getInt(this, tr("Бинарный поиск"), tr("Введите число:"),
                             0, -2147483648, 2147483647, 1, &ok);
    if (!ok) {
        value = 0;
    }

    int left = 0;
    int right = coloms.size() - 1;
    int mid;


    while (left <= right) {
        mid = left + (right - left) / 2;

        if (left >= 0 && left < coloms.size()) {
            coloms[left]->set_new_state(ColomRect::Pivot);
        }
        if (right >= 0 && right < coloms.size()) {
            coloms[right]->set_new_state(ColomRect::Pivot);
        }

        coloms[mid]->set_new_state(ColomRect::Current);
        scene->update();
        QApplication::processEvents();
        QThread::msleep(delay * 2);

        coloms[left]->set_new_state(ColomRect::Unsorted);
        coloms[right]->set_new_state(ColomRect::Unsorted);
        coloms[mid]->set_new_state(ColomRect::Unsorted);

        if (coloms[mid]->get_hight() == value) {
            coloms[mid]->set_new_state(ColomRect::state::Sorted);
            scene->update();
            QApplication::processEvents();
            QMessageBox::information(
                this, "Найден",
                QString("Элемент %1 находится на позиции %2")
                    .arg(value)
                    .arg(mid));
            return;
        } else if (coloms[mid]->get_hight() > value) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    QMessageBox::warning(this, "Сообщение", "Элемент не найден!");
}
