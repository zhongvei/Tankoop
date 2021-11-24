#include "Basic.h"
#include <QKeyEvent>
#include <cstdlib>
#include <cmath>
#include <QIcon>
#include <QPointF>
#include <QCursor>
#include <QGraphicsView>
#include <QDebug>
#include <QWidget>
#include "Bullet.h"
#include <QGraphicsScene>

Basic::Basic(QGraphicsView* parent): Tank(50,1,50,100,10,10,0,0.6,0.6,50,1,0,0),
    UP(false), DOWN(false), RIGHT(false), LEFT(false), parent(parent) {
}

// WILSON CODE TEST : KEY PRESS AND KEY RELEASE
void Basic::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
        case Qt::Key::Key_W:
            UP = true;
            break;
        case Qt::Key::Key_S:
            DOWN = true;
            break;
        case Qt::Key::Key_D:
            RIGHT = true;
            break;
        case Qt::Key::Key_A:
            LEFT = true;
            break;

    }


    if (event->key() == Qt::Key_Space){
        /* Create a bullet */
        qDebug() << "PEW-PEW";
        Bullet * bullet = new Bullet(this,get_damage(),0,10,get_bullet_speed(),get_bullet_speed());
        bullet->set_degree(this->get_degree());
        //bullet->setPos(x()+(this->get_size()/2),y()+(this->get_size()/2));
        //bullet->setPos(x()-60+(this->get_size()/2*(1+cos(bullet->get_degree()/57))),y()-60+(this->get_size()/2*(1+sin(bullet->get_degree()/57))));
        bullet->setPos(x()+(this->get_size()/2*(1+cos(bullet->get_degree()/57))),y()+(this->get_size()/2*(1+sin(bullet->get_degree()/57))));


        scene()->addItem(bullet);
    }

}


double Basic::get_changex() {
    if ( (double) RIGHT - (double) UP ||
         (double) UP - (double) LEFT  ||
         (double) LEFT - (double) DOWN||
         (double) DOWN - (double) RIGHT
         ) {
        return (this->get_vx()*((double) RIGHT - (double) LEFT)/sqrt(2))/2;
    }
    return this->get_vx()*((double) RIGHT - (double) LEFT)/2;

}
double Basic::get_changey() {
    if ( (double) RIGHT - (double) UP ||
         (double) UP - (double) LEFT  ||
         (double) LEFT - (double) DOWN||
         (double) DOWN - (double) RIGHT
         ) {
        return (this->get_vy()*((double) DOWN - (double) UP)/sqrt(2))/2;
    }
    return this->get_vy()*((double) DOWN - (double) UP)/2;
}

void Basic::keyReleaseEvent(QKeyEvent *event){
    switch(event->key()){
        case Qt::Key::Key_W:
            UP = false;
            break;
        case Qt::Key::Key_S:
            DOWN = false;
            break;
        case Qt::Key::Key_D:
            RIGHT = false;
            break;
        case Qt::Key::Key_A:
            LEFT = false;
            break;

    }

}
void Basic::advance(int step)
{
    if (!step)
        return;
    //qDebug("hi");
    facing_cursor(this);
    //qDebug("Tank Advance");
    QPointF healthpos;
    healthpos.setX(this->x());
    healthpos.setY(this->y());
    //qDebug() << healthpos;
    setFocus();

//    QPainter painter(QPaintDevice);
//    //painter.setPen(QPen(Qt::black), 1);
//    painter.drawRect(this->x(), this->y(), 200,200);

    // IF THIS BASIC IS THE USER: THEN CENTER ON. ELSE, DONT CENTER ON
    parent->centerOn(this);

}

void Basic::facing_cursor(Basic* basic) {

    QPointF cursor_position = parent->mapToScene(parent->mapFromGlobal(QCursor::pos()));
    double angle_in_radians = std::atan2((cursor_position.y()-(basic->y()+basic->get_size()/2)),(cursor_position.x()-(basic->x()+basic->get_size()/2)));
    double angle_in_degrees = (angle_in_radians / M_PI) * 180;
    set_degree(angle_in_degrees);

    QTransform transform;
    transform.translate(basic->get_size()/2,basic->get_size()/2);
    transform.rotate(angle_in_degrees);
    transform.translate(-(basic->get_size()/2),-(basic->get_size()/2));
    basic->setTransform(transform);


    QPointF tankpos;
    tankpos.setX(basic->x());
    tankpos.setY(basic->y());
    tankpos += QPointF(0,120);

    //health_bar->setPos(tankpos);

    basic->setPos(basic->x()+basic->get_changex(),basic->y()+basic->get_changey());
//    QPointF pos = health_bar->mapToItem(basic, 0, 100);
//    health_bar->setPos(pos);
}
