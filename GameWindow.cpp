#include "GameWindow.h"
#include <QGraphicsRectItem>

GameWindow::GameWindow(QWidget* parent)
{
    scene = new QGraphicsScene;
    scene->setSceneRect(0,0,1400,1000);

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1400,1000);

    QGraphicsRectItem *rect = new QGraphicsRectItem();
    rect->setRect(0,0,100,100);
    scene->addItem(rect);
    QGraphicsView *v = new QGraphicsView(scene);

    v->show();
    show();

}
