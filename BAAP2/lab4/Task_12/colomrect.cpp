#include "colomrect.h"
#include <QPainter>

ColomRect::ColomRect()
    : QGraphicsObject(nullptr),
      width(10),
      height(10),


      currnet_state(Unsorted) {}

ColomRect::ColomRect(qreal width, qreal height, QGraphicsItem* parent)
    : QGraphicsObject(parent),
      width(width),
      height(height),


      currnet_state(Unsorted) {}

void ColomRect::set_new_state(state st) {
    currnet_state = st;
    update();  // перерисовка с новым цветом
}

QBrush ColomRect::get_brush_for_state(state st) {
    switch (st) {
        case Unsorted:
            return QBrush(Qt::darkGray);
        case ActiveRange:
            return QBrush(Qt::darkGray);
        case Current:
            return QBrush(QColor(199, 21, 133));
        case Pivot:
            return QBrush(Qt::yellow);
        case Partition:
            return QBrush(Qt::darkYellow);
        case Sorted:
            return QBrush(Qt::green);
        case HeapNode:
            return QBrush(QColor(148, 0, 211));
    }
}

qreal ColomRect::get_hight() {
    return height;
}

qreal ColomRect::get_width() {
    return width;
}

void ColomRect::set_hight(qreal h) {
    prepareGeometryChange();
    height = h;
    update();
}

QRectF ColomRect::boundingRect() const {
    return QRectF(0, 0, width, height);
}

void ColomRect::paint(QPainter* painter, const QStyleOptionGraphicsItem*,
                      QWidget*) {
    painter->setBrush(get_brush_for_state(currnet_state));
    painter->drawRect(0, 0, width, height);
}
