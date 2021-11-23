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
Basic::Basic(QGraphicsView* parent
        // const double& health, const double& health_regen, const double& max_health, 
        // const int& size, const int& vx, const int& vy,const double& xp,
        // const double& attack_speed,
        // const double& bullet_speed,
        // const double& damage,
        // const int& level
        ): Tank(50,1,50,50,10,10,0,0.6,0.6,7,1),
        UP(false), DOWN(false), RIGHT(false), LEFT(false),
        parent(parent) {


}

//void Basic::keyPressEvent(QKeyEvent *event){
//    if (event->key() == Qt::Key_Left){
//        setPos(x()-this->get_vx(),y());
//    }
//    if (event->key() == Qt::Key_Right){
//        setPos(x()+this->get_vx(),y());
//    }
//    if (event->key() == Qt::Key_Up){
//        setPos(x(),y()-this->get_vy());
//    }
//    if (event->key() == Qt::Key_Down){
//        setPos(x(),y()+this->get_vy());
//    }
//}

// WILSON CODE TEST : KEY PRESS AND KEY RELEASE
void Basic::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
        case Qt::Key::Key_Up:
            UP = true;
            break;
        case Qt::Key::Key_Down:
            DOWN = true;
            break;
        case Qt::Key::Key_Right:
            RIGHT = true;
            break;
        case Qt::Key::Key_Left:
            LEFT = true;
            break;

    }
}

void Basic::keyReleaseEvent(QKeyEvent *event){
    switch(event->key()){
        case Qt::Key::Key_Up:
            UP = false;
            break;
        case Qt::Key::Key_Down:
            DOWN = false;
            break;
        case Qt::Key::Key_Right:
            RIGHT = false;
            break;
        case Qt::Key::Key_Left:
            LEFT = false;
            break;

    }
}
// WILSON CODE TEST : KEY PRESS AND KEY RELEASE

double Basic::get_changex() {
    if ( (double) RIGHT - (double) UP ||
         (double) UP - (double) LEFT  ||
         (double) LEFT - (double) DOWN||
         (double) DOWN - (double) RIGHT
         ) {
        //return sqrt(this->get_vx() * this->get_vx() + this->get_vy() * this->get_vy())/2;
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
        //return sqrt(this->get_vx() * this->get_vx() + this->get_vy() * this->get_vy())/2;
    }
    return this->get_vy()*((double) DOWN - (double) UP)/2;
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

//    QPainter painter(QPaintDevice);
//    //painter.setPen(QPen(Qt::black), 1);
//    painter.drawRect(this->x(), this->y(), 200,200);

    // IF THIS BASIC IS THE USER: THEN CENTER ON. ELSE, DONT CENTER ON
    parent->centerOn(this);

}

void Basic::facing_cursor(Basic* basic) {
    //qDebug() << parent->mapFromGlobal(QCursor::pos());
    //qDebug() << parent->mapToScene(parent->mapFromGlobal(QCursor::pos()));
    QPointF cursor_position = parent->mapToScene(parent->mapFromGlobal(QCursor::pos()));
    double angle_in_radians = std::atan2((cursor_position.y()-basic->y()),(cursor_position.x()-basic->x()));
    double angle_in_degrees = (angle_in_radians / M_PI) * 180;
    angle_in_degrees = angle_in_degrees - 90; // adjusted by -90
//    qDebug() << basic->y();
//    qDebug() << basic->x();
//    qDebug() << cursor_position.y();
//    qDebug() << cursor_position.x();
//    qDebug( "angle in degrees");
//    qDebug() << angle_in_degrees;

    QTransform transform;
    double dx = 0; double dy = 0;
    transform.translate(dx,dy);
    //transform.translate(basic->get_size()/2,basic->get_size()/2);
    transform.rotate(angle_in_degrees);
    //transform.translate(-(basic->get_size()/2),-(basic->get_size()/2));
    transform.translate(-dx,-dy);
    //basic->setTransformOriginPoint(QPoint(basic->x()+(basic->get_size()/2),basic->y()+(basic->get_size()/2)));
    basic->setTransform(transform);
    //qDebug() << transform;

    QPointF tankpos;
    tankpos.setX(basic->x());
    tankpos.setY(basic->y());
    tankpos += QPointF(0,120);

    //health_bar->setPos(tankpos);

    basic->setPos(basic->x()+basic->get_changex(),basic->y()+basic->get_changey());
//    QPointF pos = health_bar->mapToItem(basic, 0, 100);
//    health_bar->setPos(pos);
}
