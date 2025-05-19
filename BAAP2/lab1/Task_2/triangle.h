#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "figure.h"

class Triangle : public Figure {
   public:
    float size_ = 60;
    float area() override;
    float perimeter() override;

   protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*,
               QWidget*) override;
};

#endif	// TRIANGLE_H
