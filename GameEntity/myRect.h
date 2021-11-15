#ifndef MYRECT_H
#define MYRECT_H

#include <QGraphicsRectItem>

class MyRect: public QGraphicsRectItem{
public:
    void keyPressEvent(QKeyEvent * event);
private:
    QGraphicsRectItem *rect;
};

#endif // MYRECT_H
