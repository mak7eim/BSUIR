#ifndef DATE_H
#define DATE_H

#include <QDate>
#include <QtMath>

class Date {
   public:
    Date();
    Date(int year, int month, int day);
    Date NextDay();
    Date PreviousDay();
    bool IsLeap();
    short WeekNumber();
    int DaysTillYourBirthday(Date birthdaydate);
    int Duration(Date date);
    QString FromDateToString();
    Date FromQDatetoDate(QDate qdate);
    QString FromIntToString(int num);
    QString FromShortToString(short num);
    QString FromBoolToString(bool flag);

   private:
    const int year_part_start_ = 6;
    const int dateline_ = 10;
    const int weeknum_ = 7;
    int day_ = 0, month_ = 0, year_ = 0;
    short daysSinceBeggingOfYear_ = 0;
    const short monthsInYear_ = 12, daysInYear_ = 365, day31_ = 31, day28_ = 28,
                day30_ = 30, day29_ = 29, monthFebruary_ = 2;
    const short oneHundreed_ = 100, fourHundreed_ = 400;
    const short daysInPerMonth_[12] = {day31_, day28_, day31_, day30_,
                                       day31_, day30_, day31_, day31_,
                                       day30_, day31_, day30_, day31_};
};

#endif	// DATE_H
