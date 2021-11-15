#ifndef BASIC_H
#define BASIC_H

#include <QGraphicsRectItem>

#include "Tank.h"

class Basic: public Tank, public QGraphicsRectItem
{
public:
    Basic(
        // const double& health, const double& health_regen, const double& max_health, 
        // const int& size, const int& vx, const int& vy,const double& xp,
        // const double& attack_speed,
        // const double& bullet_speed,
        // const double& damage,
        // const int& level
    );
    void keyPressEvent(QKeyEvent * event);
};

#endif // BASIC_H
