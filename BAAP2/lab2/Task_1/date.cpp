#include "date.h"
#include "QDebug"

Date::Date() {
    day_ = 0;
    month_ = 0;
    year_ = 0;
}

Date::Date(int year, int month, int day) {
    day_ = day;
    month_ = month;
    year_ = year;

    daysSinceBeggingOfYear_ = 0;


    for (int i = 0; i < month_ - 1; i++) {
        daysSinceBeggingOfYear_ += daysInPerMonth_[i];
    }
    if (month_ > 2 && IsLeap()) {
        daysSinceBeggingOfYear_++;
    }
    daysSinceBeggingOfYear_ += day_;
}

Date Date::NextDay() {


    if (day_ == day29_ && month_ == monthFebruary_) {
        return Date(year_, 3, 1);
    }


    if (month_ == monthsInYear_ && day_ == day31_) {
        return Date(year_ + 1, 1, 1);
    }


    if (day_ == daysInPerMonth_[month_ - 1]) {
        return Date(year_, month_ + 1, 1);
    }
    return Date(year_, month_, day_ + 1);
}

Date Date::PreviousDay() {


    if (day_ == 1) {
        if (month_ == 1) {
            return Date(year_ - 1, monthsInYear_, day31_);
        }
        if (month_ == 3 && IsLeap()) {
            return Date(year_, monthFebruary_, day29_);
        }
        return Date(year_, month_, daysInPerMonth_[month_ - 1]);
    }
    return Date(year_, month_, day_ - 1);
}

bool Date::IsLeap() {
    if ((year_ % 4 == 0) &&
        (year_ % oneHundreed_ != 0 || year_ % fourHundreed_ == 0)) {
        return (year_ % 4 == 0) &&
               (year_ % oneHundreed_ != 0 || year_ % fourHundreed_ == 0);
    }
    return false;
}

short Date::WeekNumber() {
    return (daysSinceBeggingOfYear_ / weeknum_) +
           ((daysSinceBeggingOfYear_ % weeknum_ == 0) ? 0 : 1);
}

int Date::Duration(Date date) {
    int my_days = (year_ * daysInYear_) + day_;


    for (int i = 0; i < month_ - 1; ++i) {
        my_days += daysInPerMonth_[i];
    }
    int temp_year = year_;


    if (month_ <= 2) {
        temp_year--;
    }
    my_days +=
        temp_year / 4 - temp_year / oneHundreed_ + temp_year / fourHundreed_;

    int date_days = (date.year_ * daysInYear_) + date.day_;


    for (int i = 0; i < date.month_ - 1; ++i) {
        date_days += daysInPerMonth_[i];
    }
    temp_year = date.year_;


    if (date.month_ <= 2) {
        temp_year--;
    }
    date_days +=
        temp_year / 4 - temp_year / oneHundreed_ + temp_year / fourHundreed_;

    return (abs(my_days - date_days));
}


int Date::DaysTillYourBirthday(Date birthdaydate) {
    int birthdaydate_year = year_;


    if (birthdaydate.day_ == day_ && birthdaydate.month_ == month_) {
        return 0;
    }


    if (birthdaydate.day_ < day_ && birthdaydate.month_ < month_) {
        birthdaydate_year++;
    }

    return Date::Duration(
        Date(birthdaydate_year, birthdaydate.month_, birthdaydate.day_));
}

QString Date::FromDateToString() {
    return QDate(year_, month_, day_).toString("dd.MM.yyyy");
}

Date Date::FromQDatetoDate(QDate qdate) {
    QString formatted_q_date = qdate.toString("dd.MM.yyyy");
    QString str_day = "", str_month = "", str_year = "";


    for (int i = 0; i < dateline_; i++) {
        if (i >= 0 && i <= 1) {
            str_day += formatted_q_date.at(i);
        }

        if (i >= 3 && i <= 4) {
            str_month += formatted_q_date.at(i);
        }

        if (i >= year_part_start_) {
            str_year += formatted_q_date.at(i);
        }
    }

    int day = str_day.toInt(), month = str_month.toInt(),
        year = str_year.toInt();
    return Date(year, month, day);
}

QString Date::FromIntToString(int num) {
    return QString::number(num);
}

QString Date::FromShortToString(short num) {
    return QString::number(num);
}

QString Date::FromBoolToString(bool flag) {


    if (flag) {
        return "Yes";
    }
    return "No";
}
