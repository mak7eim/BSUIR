#include "figure.h"


QRectF Figure::boundingRect() const {
    return QRectF(-500, -500, 1000, 1000);
}

float Figure::getScale() {
    return scale_;
}

QPoint Figure::getCenter() {
    return QPoint(this->x(), this->y());
}

bool Figure::getItem() {
    return Flag_;
}

void Figure::setItem(bool flag) {
    Flag_ = flag;
}

void Figure::getSize() {
    if (this->getItem()) {
        scale_ += 0.01;
    } else {
        scale_ -= 0.01;


        if (scale_ < 0) {
            scale_ = 0.01;
        }
    }

    this->setScale(scale_);
}

void Figure::move_up() {
    this->setPos(this->x(), this->y() - 2);
}

void Figure::move_down() {
    this->setPos(this->x(), this->y() + 2);
}

void Figure::move_left() {
    this->setPos(this->x() - 2, this->y());
}

void Figure::move_right() {
    this->setPos(this->x() + 2, this->y());
}

void Figure::rotate_right() {
    ++angle_;
    this->setRotation(angle_);
}

void Figure::rotate_left() {
    --angle_;
    this->setRotation(angle_);
}

float Figure::area() {
    return 0;
}

float Figure::perimeter() {
    return 0;
}

void Figure::paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) {}
