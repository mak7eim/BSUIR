#ifndef MOVINGRECTANGLE_H
#define MOVINGRECTANGLE_H
#include <QPainter>
#include <QWidget>

class Rectangle : public QWidget {
   public:
    void paintEvent(QPaintEvent*) override;
    void drawRec(QPainter* painter);
    void Up();
    void Down();

   private:
    int angle_ = 0;
};

#endif
