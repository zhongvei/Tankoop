#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include "myRect.h"

class MyRect;

class View: public QGraphicsView
{
    Q_OBJECT
public:
    View(QGraphicsView *parent = nullptr);
    void moveView(MyRect* rect, int x, int y);
private:
    float x;
    float y;
};

#endif // VIEW_H
