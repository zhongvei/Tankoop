#ifndef MYRECT_H
#define MYRECT_H

#include <QGraphicsRectItem>
#include"QGraphicsScene"

class MyRect: public QGraphicsRectItem{
public:
    void keyPressEvent(QKeyEvent * event);
private:

};

#endif // MYRECT_H
