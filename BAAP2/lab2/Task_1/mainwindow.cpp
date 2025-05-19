#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
    ui_->setupUi(this);
}

void MainWindow::changeEvent(QEvent* e) {
    if (e->type() == QEvent::ActivationChange && this->isActiveWindow()) {


        if (filePath_ != "") {
            readTextFile();
        }
    }
}

MainWindow::~MainWindow() {
    delete ui_;
}


void MainWindow::readTextFile() {
    if (filePath_.isEmpty()) {
        return;
    }

    file_.setFileName(filePath_);
    if (!file_.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream file_stream(&file_);
    QString s;
    do {
        file_stream >> s;
        if (!s.isEmpty()) {
            if (s.endsWith('\\')) {
                s.chop(1);
            }
            if (checkDateLine(s)) {
                addDateToVector(s);
            } else {
                QMessageBox::warning(this, "Warning", "Wrong data");
                ui_->tableWidget->setRowCount(0);
                return;
            }
        }
    } while (!file_stream.atEnd());

    ui_->tableWidget->setRowCount(dates_.size());
    for (int i = 0; i < dates_.size(); ++i) {
        auto item0 = new QTableWidgetItem(dates_[i].FromDateToString());
        ui_->tableWidget->setItem(i, 0, item0);

        auto item1 =
            new QTableWidgetItem(dates_[i].NextDay().FromDateToString());
        ui_->tableWidget->setItem(i, 1, item1);

        auto item2 =
            new QTableWidgetItem(dates_[i].PreviousDay().FromDateToString());
        ui_->tableWidget->setItem(i, 2, item2);

        auto item3 = new QTableWidgetItem(
            dates_[i].FromShortToString(dates_[i].WeekNumber()));
        ui_->tableWidget->setItem(i, 3, item3);

        auto item4 = new QTableWidgetItem(
            dates_[i].FromBoolToString(dates_[i].IsLeap()));
        ui_->tableWidget->setItem(i, 4, item4);

        auto item6 = new QTableWidgetItem(dates_[i].FromIntToString(
            dates_[i].Duration(dates_[i].FromQDatetoDate(currentDate_))));
        ui_->tableWidget->setItem(i, tablenum6_, item6);

        if (i < dates_.size() - 1) {
            auto item7 = new QTableWidgetItem(
                dates_[i].FromIntToString(dates_[i].Duration(dates_[i + 1])));
            ui_->tableWidget->setItem(i, tablenum7_, item7);
        } else {
            auto item7 = new QTableWidgetItem("-");
            ui_->tableWidget->setItem(i, tablenum7_, item7);
        }
    }

    file_.close();
}

bool MainWindow::checkDateLine(QString dateLine) {
    if (dateLine.length() != dateline_) {
        return false;
    }


    for (int i = 0; i < dateline_; i++) {
        if (i == 0 || i == 1 || i == 3 || i == 4 ||
            (i >= dateline_ - 4 && i < dateline_)) {
            if (dateLine[i] < '0' || dateLine[i] > '9') {
                return false;
            }
        } else {
            if (dateLine[i] != '.') {
                return false;
            }
        }
    }

    QStringList date_parts = dateLine.split('.');
    int day = date_parts[0].toInt();
    int month = date_parts[1].toInt();
    int year = date_parts[2].toInt();


    if (month < 1 || month > yearmonth_ || day < 1) {
        return false;
    }

    const int days_in_month[] = {0,	 31, 28, 31, 30, 31, 30,
                                 31, 31, 30, 31, 30, 31};
    bool is_leap_year = (year % 4 == 0);


    if (is_leap_year && month == 2) {
        return (day <= vesyear_);
    } else {
        return (day <= days_in_month[month]);
    }
}

void MainWindow::addDateToVector(QString dateLine) {
    QString str_day, str_month, str_year;


    for (int i = 0; i < date_string_length_; i++) {
        if (i >= 0 && i <= 1) {
            str_day += dateLine[i];
        }

        if (i >= 3 && i <= 4) {
            str_month += dateLine[i];
        }

        if (i >= year_part_start_) {
            str_year += dateLine[i];
        }
    }

    int day = str_day.toInt(), month = str_month.toInt(),
        year = str_year.toInt();
    Date date(year, month, day);
    dates_.push_back(date);
}


void MainWindow::on_open_file_button_clicked() {
    filePath_ = QFileDialog::getOpenFileName(
        nullptr, "Выберите файл", QDir::homePath(), "Текстовые файлы (*.txt)");

    readTextFile();
}

void MainWindow::on_push_button_birthday_date_clicked() {
    QString str_day, str_month, str_year;

    birthdayDate_ = ui_->lineEdit->text();
    if (!checkDateLine(birthdayDate_)) {
        QMessageBox::warning(this, "Warning", "Wrong data");
        return;
    }

    isBirthdayShow_ = true;


    for (int i = 0; i < date_string_length_; i++) {
        if (i >= 0 && i <= 1) {
            str_day += birthdayDate_[i];
        }

        if (i >= 3 && i <= 4) {
            str_month += birthdayDate_[i];
        }

        if (i >= year_part_start_) {
            str_year += birthdayDate_[i];
        }
    }

    int day = str_day.toInt(), month = str_month.toInt(),
        year = str_year.toInt();
    Date birthday_date(year, month, day);

    for (int i = 0; i < dates_.size(); ++i) {
        auto item5 = new QTableWidgetItem(dates_[i].FromIntToString(
            dates_[i].DaysTillYourBirthday(birthday_date)));
        ui_->tableWidget->setItem(i, tablenum5_, item5);
    }
}


void MainWindow::on_push_button_add_date_clicked() {
    QString date_line = ui_->lineEdit_2->text();

    if (!checkDateLine(date_line)) {
        QMessageBox::warning(this, "Warning", "Wrong data");
        return;
    }

    addDateToVector(date_line);

    QString str_day, str_month, str_year;


    for (int i = 0; i < date_string_length_; i++) {
        if (i >= 0 && i <= 1) {
            str_day += date_line[i];
        }

        if (i >= 3 && i <= 4) {
            str_month += date_line[i];
        }

        if (i >= year_part_start_) {
            str_year += date_line[i];
        }
    }

    int day = str_day.toInt(), month = str_month.toInt(),
        year = str_year.toInt();
    Date date(year, month, day);

    int row = ui_->tableWidget->rowCount();
    ui_->tableWidget->insertRow(row);

    auto item0 = new QTableWidgetItem(date.FromDateToString());
    ui_->tableWidget->setItem(row, 0, item0);

    auto item1 = new QTableWidgetItem(date.NextDay().FromDateToString());
    ui_->tableWidget->setItem(row, 1, item1);

    auto item2 = new QTableWidgetItem(date.PreviousDay().FromDateToString());
    ui_->tableWidget->setItem(row, 2, item2);

    auto item3 =
        new QTableWidgetItem(date.FromShortToString(date.WeekNumber()));
    ui_->tableWidget->setItem(row, 3, item3);

    auto item4 = new QTableWidgetItem(date.FromBoolToString(date.IsLeap()));
    ui_->tableWidget->setItem(row, 4, item4);

    auto item6 = new QTableWidgetItem(date.FromIntToString(
        date.Duration(date.FromQDatetoDate(currentDate_))));
    ui_->tableWidget->setItem(row, tablenum6_, item6);

    if (row < dates_.size() - 1) {
        auto item7 = new QTableWidgetItem(
            dates_[row].FromIntToString(dates_[row].Duration(dates_[row + 1])));
        ui_->tableWidget->setItem(row, tablenum7_, item7);
    } else {
        auto item7 = new QTableWidgetItem("-");
        ui_->tableWidget->setItem(row, tablenum7_, item7);
    }


    if (row > 0) {
        auto item8 = new QTableWidgetItem(dates_[row - 1].FromIntToString(
            dates_[row - 1].Duration(dates_[row])));
        ui_->tableWidget->setItem(row - 1, tablenum7_, item8);
    }


    if (isBirthdayShow_) {
        QString str_day, str_month, str_year;
        for (int i = 0; i < date_string_length_; i++) {
            if (i >= 0 && i <= 1) {
                str_day += birthdayDate_[i];
            }

            if (i >= 3 && i <= 4) {
                str_month += birthdayDate_[i];
            }

            if (i >= year_part_start_) {
                str_year += birthdayDate_[i];
            }
        }

        int day = str_day.toInt(), month = str_month.toInt(),
            year = str_year.toInt();
        Date birthday_date(year, month, day);

        auto item5 = new QTableWidgetItem(dates_[row].FromIntToString(
            dates_[row].DaysTillYourBirthday(birthday_date)));
        ui_->tableWidget->setItem(row, tablenum5_, item5);
    }

    if (file_.open(QIODevice::WriteOnly | QIODevice::Append |
                   QIODevice::Text)) {
        QTextStream stream(&file_);
        stream << date_line << "\n";
        file_.close();
    }
    ui_->tableWidget->update();
}


void MainWindow::on_push_button_edit_clicked() {
    int index = ui_->spinBox->value();

    if (index < 1 || index > dates_.size()) {
        QMessageBox::warning(this, "Warning", "Wrong data");
        return;
    }

    index--;

    QString date_line = ui_->lineEdit_3->text();

    if (!checkDateLine(date_line)) {
        QMessageBox::warning(this, "Warning", "Wrong data");
        return;
    }

    file_.open(QIODevice::ReadWrite);
    QTextStream file_stream(&file_);
    file_stream.seek((index) * (date_string_length_ + 1) * sizeof(char));
    file_stream << date_line << "\n";

    QString str_day, str_month, str_year;


    for (int i = 0; i < date_string_length_; i++) {
        if (i >= 0 && i <= 1) {
            str_day += date_line[i];
        }

        if (i >= 3 && i <= 4) {
            str_month += date_line[i];
        }

        if (i >= year_part_start_) {
            str_year += date_line[i];
        }
    }

    int day = str_day.toInt(), month = str_month.toInt(),
        year = str_year.toInt();
    Date date(year, month, day);

    auto item0 = new QTableWidgetItem(date.FromDateToString());
    ui_->tableWidget->setItem(index, 0, item0);

    auto item1 = new QTableWidgetItem(date.NextDay().FromDateToString());
    ui_->tableWidget->setItem(index, 1, item1);

    auto item2 = new QTableWidgetItem(date.PreviousDay().FromDateToString());
    ui_->tableWidget->setItem(index, 2, item2);

    auto item3 =
        new QTableWidgetItem(date.FromShortToString(date.WeekNumber()));
    ui_->tableWidget->setItem(index, 3, item3);

    auto item4 = new QTableWidgetItem(date.FromBoolToString(date.IsLeap()));
    ui_->tableWidget->setItem(index, 4, item4);

    auto item6 = new QTableWidgetItem(date.FromIntToString(
        date.Duration(date.FromQDatetoDate(currentDate_))));
    ui_->tableWidget->setItem(index, tablenum6_, item6);

    if (index < dates_.size() - 1) {
        auto item7 = new QTableWidgetItem(
            date.FromIntToString(date.Duration(dates_[index + 1])));
        ui_->tableWidget->setItem(index, tablenum7_, item7);
    } else {
        auto item7 = new QTableWidgetItem("-");
        ui_->tableWidget->setItem(index, tablenum7_, item7);
    }


    if (index > 0) {
        auto item8 = new QTableWidgetItem(dates_[index - 1].FromIntToString(
            dates_[index - 1].Duration(date)));
        ui_->tableWidget->setItem(index - 1, tablenum7_, item8);
    }


    if (isBirthdayShow_) {
        QString str_day, str_month, str_year;
        for (int i = 0; i < date_string_length_; i++) {
            if (i >= 0 && i <= 1) {
                str_day += birthdayDate_[i];
            }

            if (i >= 3 && i <= 4) {
                str_month += birthdayDate_[i];
            }

            if (i >= year_part_start_) {
                str_year += birthdayDate_[i];
            }
        }

        int day = str_day.toInt(), month = str_month.toInt(),
            year = str_year.toInt();
        Date birthday_date(year, month, day);

        auto item5 = new QTableWidgetItem(
            date.FromIntToString(date.DaysTillYourBirthday(birthday_date)));
        ui_->tableWidget->setItem(index, tablenum5_, item5);
    }

    ui_->tableWidget->update();

    file_.close();
}

void MainWindow::update() {
    readTextFile();
}
