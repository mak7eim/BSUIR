#include "item.h"

Item::Item(long double x, long double y, long double w, long double h,
           int number)
    : QObject(), QGraphicsItem() {
    timer = new QTimer(this);
    setPos((x - w) / 2, y - h);
    this->w = w;
    this->h = h;
    num = number;
}

void Item::up() {
    connect(timer, &QTimer::timeout, this, &Item::mup);
    timer->start(10);
}

void Item::mB(int n, int speed) {
    this->n = n;
    timer->stop();
    connect(timer, &QTimer::timeout, this, &Item::mup);
    timer->start(speed);
    if (pos().x() < -w / 2) {
        connect(this, &Item::mupFinished, this, &Item::rB);
        connect(this, &Item::mrFinished, this, &Item::mDown);
    } else if (pos().x() > -w / 2) {
        connect(this, &Item::mupFinished, this, &Item::lB);
        connect(this, &Item::mlFinished, this, &Item::mDown);
    }
}

void Item::mC(int n, int speed) {
    this->n = n;
    timer->stop();
    connect(timer, &QTimer::timeout, this, &Item::mup);
    timer->start(speed);
    connect(this, &Item::mupFinished, this, &Item::rC);
    connect(this, &Item::mrFinished, this, &Item::mDown);
}

void Item::mA(int n, int speed) {
    this->n = n;
    timer->stop();
    connect(timer, &QTimer::timeout, this, &Item::mup);
    timer->start(speed);
    connect(this, &Item::mupFinished, this, &Item::lA);
    connect(this, &Item::mlFinished, this, &Item::mDown);
}

void Item::paint(QPainter* painter, const QStyleOptionGraphicsItem* ooption,
                 QWidget* wwidget) {
    Q_UNUSED(ooption);
    Q_UNUSED(wwidget);
    QRectF rect = boundingRect();
    QBrush brush;
    if (num % 2 == 1) {
        brush = QBrush(Qt::red);
    } else {
        brush = QBrush(Qt::black);
    }

    painter->setBrush(brush);

    const qreal corner_radius = 5.0;
    painter->drawRoundedRect(rect, corner_radius, corner_radius);

    painter->setPen(Qt::white);
    QFont font("TimesNewRoman", 9);
    painter->setFont(font);
    QString number = QString::number(num);
    QPointF text_position =
        rect.center() - QPointF(font.pointSizeF() * number.length() / 2, 0);
    painter->drawText(text_position, number);
}

void Item::lA() {
    ml(-400);
}

void Item::rB() {
    mr(0);
}

void Item::lB() {
    ml(0);
}

void Item::rC() {
    mr(400);
}

void Item::md(int n) {

    connect(timer, &QTimer::timeout, this, [this, n]() {
        if (pos().y() >= 150 - n * h - h) {
            disconnect(timer, &QTimer::timeout, this, nullptr);
            disconnect(this, &Item::mrFinished, this, &Item::mDown);
            disconnect(this, &Item::mlFinished, this, &Item::mDown);
            if (pos().x() == (400 - w) / 2) {
                emit mCFinished();
            }
            if (pos().x() == (-400 - w) / 2) {
                emit mAFinished();
            }
            if (pos().x() == (0 - w) / 2) {
                emit mBFinished();
            }
            emit mdFinished();
        } else {
            this->setPos(this->pos().rx(), this->pos().ry() + difcord);
        }
    });
}

QRectF Item::boundingRect() const {
    return QRectF(0, 0, w, h);
}

void Item::mup() {
    if (pos().y() <= -300) {
        disconnect(timer, &QTimer::timeout, this, &Item::mup);

        emit mupFinished();
    }
    this->setPos(this->pos().rx(), this->pos().ry() - difcord);
}

void Item::ml(double x) {

    connect(timer, &QTimer::timeout, this, [this, x]() {
        if (pos().x() <= (x - w) / 2) {
            disconnect(this, &Item::mupFinished, this, &Item::lB);
            disconnect(this, &Item::mupFinished, this, &Item::lA);
            disconnect(timer, &QTimer::timeout, this, nullptr);
            emit mlFinished();

        } else {
            this->setPos(this->pos().rx() - difcord, this->pos().ry());
        }
    });
}

void Item::mr(double x) {

    connect(timer, &QTimer::timeout, this, [this, x]() {
        if (pos().x() >= (x - w) / 2) {
            disconnect(this, &Item::mupFinished, this, &Item::rC);
            disconnect(this, &Item::mupFinished, this, &Item::rB);
            disconnect(timer, &QTimer::timeout, this, nullptr);
            emit mrFinished();
        } else {
            this->setPos(this->pos().rx() + difcord, this->pos().ry());
        }
    });
}

void Item::mDown() {
    md(n);
}
