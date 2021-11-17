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
    facing_cursor(basic);
}

void GameWindow::facing_cursor(Basic* basic) {
    QPointF cursor_position = mapToScene(QWidget::mapFromGlobal(QCursor::pos()));
    double angle_in_radians = std::atan2((cursor_position.y()-basic->y()),(cursor_position.x()-basic->x()));
    double angle_in_degrees = (angle_in_radians / M_PI) * 180;

    QTransform transform;
    transform.translate(basic->get_size()/2,basic->get_size()/2);
    transform.rotate(angle_in_degrees);
    transform.translate(-(basic->get_size()/2),-(basic->get_size()/2));
    //basic->setTransformOriginPoint(QPoint(basic->x()+(basic->get_size()/2),basic->y()+(basic->get_size()/2)));
    basic->setTransform(transform);
}
