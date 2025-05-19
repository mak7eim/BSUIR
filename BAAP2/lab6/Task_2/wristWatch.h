#ifndef WRISTWATCH_H
#define WRISTWATCH_H
#include <QChar>

struct WristWatch
{
    int numberOfDiamond;
    double price;
    QChar Model;
    bool isexpensivewristwatch;
    static const int MAX_NAME_SIZE = 20;
    static const int MAX_TIME_AMOUNT = 6;
    QChar brandName[MAX_NAME_SIZE];
    int worldTimeOffsets[MAX_TIME_AMOUNT] = {0,0,0,0,0,0};
};
#endif // WRISTWATCH_H
