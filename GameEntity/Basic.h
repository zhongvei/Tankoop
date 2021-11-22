#ifndef BASIC_H
#define BASIC_H

#include <QGraphicsRotation>
#include <QTransform>

#include "Tank.h"

class Basic: public Tank, public QGraphicsRotation, public QTransform
{

private:
    bool UP, DOWN, RIGHT, LEFT;

public:
    Basic(
        // const double& health, const double& health_regen, const double& max_health, 
        // const int& size, const int& vx, const int& vy,const double& xp,
        // const double& attack_speed,
        // const double& bullet_speed,
        // const double& damage,
        // const int& level
    );
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    double get_changex() const{ return this->get_vx()*((double) RIGHT - (double) LEFT)/100; }
    double get_changey() const{ return this->get_vy()*((double) DOWN - (double) UP)/100; }

};

#endif // BASIC_H
