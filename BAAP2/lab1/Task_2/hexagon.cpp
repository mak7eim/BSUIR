#include "hexagon.h"

void Hexagon::paint(QPainter* painter, const QStyleOptionGraphicsItem*,
                    QWidget*) {
    QPolygon polygon;
    polygon << QPoint(-kRadius, 0) << QPoint(-kRadius / 2, kRadius * sqrt(3) / 2)
            << QPoint(kRadius / 2, kRadius * sqrt(3) / 2) << QPoint(kRadius, 0)
            << QPoint(kRadius / 2, -kRadius * sqrt(3) / 2)
            << QPoint(-kRadius / 2, -kRadius * sqrt(3) / 2);
    painter->drawPolygon(polygon);
}

float Hexagon::area() {
    return this->getScale() * this->getScale() * 3 * kRadius * kRadius * sqrt(3) /
           2;
}

float Hexagon::perimeter() {
    return 6 * kRadius * this->getScale();
}
