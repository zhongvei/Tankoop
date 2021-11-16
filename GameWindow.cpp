#include "GameWindow.h"
#include <QGraphicsRectItem>
#include "GameEntity/myRect.h"
#include "GameEntity/View.h"
GameWindow::GameWindow(QWidget* parent)
{
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setFixedSize(800,600);
    setSceneRect(0,0,1000000,1000000);

    MyRect* enemy = new MyRect();
    enemy->setRect(0,0,100,100);
    enemy->setPos(100,100);
    scene->addItem(enemy);

    basic = new Basic();
    basic->setRect(0,0,100,100);
    basic->setPos(350,250);
    scene->addItem(basic);

    centerOn(QPoint(100,100));
    basic->setFlag(QGraphicsItem::ItemIsFocusable);
    basic->setFocus();
    show();

    //mainloop
    loop_timer = new QTimer{this};
    connect(loop_timer, &QTimer::timeout, this, &GameWindow::main_loop);
    loop_timer->start();
    // 50 updates per second

}

void GameWindow::main_loop() {
//    float x = rect->x();
//    float y = rect->y();
    centerOn(basic);
}
