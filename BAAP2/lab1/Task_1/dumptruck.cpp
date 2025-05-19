#include "dumptruck.h"

void DumpTruck::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    drawSam(&painter);
}

void DumpTruck::drawSam(QPainter* painter) {
    drawRec(painter);

    QPolygon korpus;
    korpus << QPoint(225, 185) << QPoint(150, 185) << QPoint(120, 215)
           << QPoint(105, 275) << QPoint(105, 375) << QPoint(225, 375);

    painter->setBrush(Qt::green);
    painter->drawPolygon(korpus);

    QPolygon korpus_down;
    korpus_down << QPoint(225, 375) << QPoint(510, 375) << QPoint(510, 320)
                << QPoint(225, 320);

    painter->setBrush(Qt::gray);
    painter->drawPolygon(korpus_down);

    QPolygon window;
    window << QPoint(165, 215) << QPoint(120, 215) << QPoint(105, 275)
           << QPoint(165, 275);

    painter->setBrush(Qt::blue);
    painter->drawPolygon(window);

    painter->setBrush(Qt::black);
    painter->drawEllipse(150, 350, 55, 55);
    painter->drawEllipse(345, 350, 55, 55);
    painter->drawEllipse(435, 350, 55, 55);

    painter->setBrush(Qt::gray);
    painter->drawEllipse(166, 366, 23, 23);
    painter->drawEllipse(361, 366, 23, 23);
    painter->drawEllipse(451, 366, 23, 23);
}
