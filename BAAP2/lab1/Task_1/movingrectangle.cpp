#include "movingrectangle.h"

void Rectangle::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    drawRec(&painter);
}

void Rectangle::drawRec(QPainter* painter) {
    painter->save();

    QTransform transform;
    transform.translate(510, 320);
    transform.rotate(angle_);
    transform.translate(-510, -320);
    painter->setTransform(transform);

    painter->setBrush(Qt::yellow);
    painter->drawRect(230, 170, 280, 150);
    painter->restore();
}

void Rectangle::Up() {


    if (angle_ < 90 && angle_ >= 0) {
        angle_++;
        repaint();
    }
}

void Rectangle::Down() {


    if (angle_ > 0 && angle_ <= 90) {
        angle_--;
        repaint();
    }
}
