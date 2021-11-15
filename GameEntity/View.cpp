#include "View.h"
#include <QDebug>

const int LEAP_AMOUNT = 7;

View::View(QGraphicsView *parent): QGraphicsView(parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFocusPolicy(Qt::NoFocus);
}

void View::moveView(MyRect *rect, int x, int y) {
    this->x += ((rect->x() + 100/2) - x) / LEAP_AMOUNT;
    this->y += ((rect->y() + 100/2) - y) / LEAP_AMOUNT;
    centerOn(QPointF(x, y));
    //centerOn(player->pos());
    update();
}
