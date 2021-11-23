#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include "Tank.h"
#include <QGraphicsRotation>
#include <QTransform>
#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <QPointF>
#include <QLineF>

class Enemy: public QObject, public QTransform, public Tank
{
    Q_OBJECT
public:
    Enemy(double attack_range,const int& size
            // const double& health, const double& health_regen, const double& max_health,
            // const int& size, const int& vx, const int& vy,const double& xp,
            // const double& attack_speed,
            // const double& bullet_speed,
            // const double& damage,
            // const int& level
         );
    QGraphicsEllipseItem* get_attack_area(){ return attack_area; }
    int get_range() const { return attack_range; }
    double get_scale() const { return scale; }
    void fire();
    double distanceTo(QGraphicsItem * item);

public slots:
    void move();

private:
    int num_target;
    double attack_range;
    double scale;
    QGraphicsEllipseItem *attack_area;
    QPointF attack_dest;
};

#endif // ENEMY_H



