#ifndef COLOMRECT_H
#define COLOMRECT_H

#include <QBrush>
#include <QGraphicsObject>
#include <QPainter>

class ColomRect : public QGraphicsObject {
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)  // для QPropertyAnimation

   public:
    enum state {
        Unsorted,
        ActiveRange,
        Current,
        Pivot,
        Partition,
        Sorted,
        HeapNode
    };

    ColomRect();
    ColomRect(qreal width, qreal height, QGraphicsItem* parent = nullptr);

    void set_new_state(state st);
    static QBrush get_brush_for_state(state state);

    qreal get_hight();
    qreal get_width();
    void set_hight(qreal h);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
               QWidget* widget) override;

   private:
    qreal height;
    qreal width;
    state currnet_state;
};

#endif	// COLOMRECT_H
