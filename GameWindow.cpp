#include "GameWindow.h"
#include <QGraphicsRectItem>
#include "GameEntity/myRect.h"
#include "GameEntity/View.h"
GameWindow::GameWindow(QWidget* parent)
{
    scene = new QGraphicsScene;
    scene->setSceneRect(0,0,800,600);

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);

    MyRect *rect = new MyRect();
    rect->setRect(0,0,100,100);
    rect->setPos(350,250);
    scene->addItem(rect);
    centerOn(QPoint(650,650));
    rect->setFlag(QGraphicsItem::ItemIsFocusable);
    rect->setFocus();
    show();

}
