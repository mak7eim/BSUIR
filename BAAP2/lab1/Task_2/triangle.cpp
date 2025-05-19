#include "triangle.h"

void Triangle::paint(QPainter* painter, const QStyleOptionGraphicsItem*,
                     QWidget*) {
    QPolygon polygon;
    polygon << QPoint(-60, 30 * sqrt(3)) << QPoint(0, -20 * sqrt(3))
            << QPoint(60, 30 * sqrt(3));
    painter->drawPolygon(polygon);
}

float Triangle::area() {
    return this->getScale() * this->getScale() * (size_ * size_ * sqrt(3)) / 4;
}

float Triangle::perimeter() {
    return 3 * size_ * this->getScale();
}
