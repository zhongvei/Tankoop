#ifndef BASIC_H
#define BASIC_H

#include <QGraphicsRotation>
#include <QTransform>

#include "Tank.h"

class Basic: public Tank, public QGraphicsRotation, public QTransform
{
    enum class KEY{
        NONE,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

private:
    double changex = 0;
    double changey = 0;
    KEY pressed_key_x = KEY::NONE;
    KEY released_key_x = KEY::NONE;
    KEY pressed_key_y = KEY::NONE;
    KEY released_key_y = KEY::NONE;
    void set_pressed_key_x(KEY key){ pressed_key_x = key; }
    void set_released_key_x(KEY key){ released_key_x = key; }
    void set_pressed_key_y(KEY key){ pressed_key_y = key; }
    void set_released_key_y(KEY key){ released_key_y = key; }

public:
    Basic(
        // const double& health, const double& health_regen, const double& max_health, 
        // const int& size, const int& vx, const int& vy,const double& xp,
        // const double& attack_speed,
        // const double& bullet_speed,
        // const double& damage,
        // const int& level,
        // const int& skill_point,
        // const double& degree
    );
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    double get_changex() const{ return changex/100; }
    double get_changey() const{ return changey/100; }
    KEY get_pressed_key_x() const{ return pressed_key_x; }
    KEY get_released_key_x() const{ return released_key_x; }
    KEY get_pressed_key_y() const{ return pressed_key_y; }
    KEY get_released_key_y() const{ return released_key_y; }
};

#endif // BASIC_H
