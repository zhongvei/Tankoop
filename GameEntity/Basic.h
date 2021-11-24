#ifndef BASIC_H
#define BASIC_H

#include "Tank.h"
#include "tankgraphic.h"

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsRotation>
#include <QTransform>

class Basic: public Tank, public QGraphicsRotation, public QTransform
{
private:
    double changex = 0;
    double changey = 0;
    QGraphicsView* parent = nullptr;

    bool UP, DOWN, RIGHT, LEFT;

public:

    Basic(QGraphicsView* parent=nullptr);
    void keyPressEvent(QKeyEvent * event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void facing_cursor(Basic* basic);
    double get_changex();
    double get_changey();

protected:
    void advance(int step) override;
};

#endif // BASIC_H
