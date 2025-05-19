#ifndef FIGURE_H
#define FIGURE_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QWidget>
#include <QtWidgets>
#include <cmath>


class Figure : public QGraphicsScene, public QGraphicsItem {
   public:
    bool getItem();
    void setItem(bool);
    virtual float area();
    virtual float perimeter();
    float getScale();
    QPoint getCenter();
    void getSize();
    void move_up();
    void move_down();
    void move_left();
    void move_right();
    void rotate_right();
    void rotate_left();

   private:
    bool Flag_;
    float angle_ = 0;
    float scale_ = 1.0;
    QPointF previousPoint_;

   protected:
    QRectF boundingRect() const;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem*,
                       QWidget*);
    Figure* currentItem_;
};

#endif	// FIGURE_H
