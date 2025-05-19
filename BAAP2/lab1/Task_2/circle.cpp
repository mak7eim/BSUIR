#include "circle.h"

void Circle::paint(QPainter* painter, const QStyleOptionGraphicsItem*,
                   QWidget*) {
    painter->drawEllipse(-kRadius / 2, -kRadius / 2, kRadius, kRadius);
}

float Circle::area() {
    return this->getScale() * this->getScale() * M_PI * kRadius * kRadius;
}

float Circle::perimeter() {
    return 2 * M_PI * kRadius * this->getScale();
}
