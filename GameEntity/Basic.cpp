#include "Basic.h"
#include <QKeyEvent>

Basic::Basic(
        // const double& health, const double& health_regen, const double& max_health, 
        // const int& size, const int& vx, const int& vy,const double& xp,
        // const double& attack_speed,
        // const double& bullet_speed,
        // const double& damage,
        // const int& level
        ): Tank(50,1,50,100,10,10,0,0.6,0.6,7,1,0) {}

void Basic::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Left){
        setPos(x()-this->get_vx(),y());
    }
    if (event->key() == Qt::Key_Right){
        setPos(x()+this->get_vx(),y());
    }
    if (event->key() == Qt::Key_Up){
        setPos(x(),y()-this->get_vy());
    }
    if (event->key() == Qt::Key_Down){
        setPos(x(),y()+this->get_vy());
    }
}
