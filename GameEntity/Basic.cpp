#include "Basic.h"
#include <QKeyEvent>
#include "Bullet.h"
#include <QGraphicsScene>
#include <QDebug>

Basic::Basic(
        // const double& health, const double& health_regen, const double& max_health, 
        // const int& size, const int& vx, const int& vy,const double& xp,
        // const double& attack_speed,
        // const double& bullet_speed,
        // const double& damage,
        // const int& level
        ): Tank(50,1,50,100,10,10,0,0.6,0.6,7,1,0), UP(false), DOWN(false), RIGHT(false), LEFT(false){
}

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

    if (event->key() == Qt::Key_Space){
        /* Create a bullet */
        qDebug() << "PEW-PEW";
        Bullet * bullet = new Bullet(*this,50,0,0,0);
        bullet->setPos(x()+20,y()-10);
        scene()->addItem(bullet);
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
