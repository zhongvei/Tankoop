#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsRotation>
#include <QTransform>
#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <QPointF>
#include <QLineF>
#include "Block.h"
#include "Basic.h"

class Enemy: public QObject, public QTransform, public Tank
{
    Q_OBJECT
    enum class STATE{FARMING, CHASING, RUNNING};
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
    QGraphicsEllipseItem* get_sight_area(){ return sight_area; }
    int get_range() const { return attack_range; }
    double get_attack_scale() const { return attack_scale; }
    double get_sight_scale() const { return sight_scale; }

    void fire(bool &reload);

    double distanceTo(Block * item);
    double distanceTo(Basic * basic);
    ~Enemy();

public slots:
    void move();

private:
    int num_target;
    double attack_range;
    double attack_scale;
    double sight_scale;
    STATE current_state = STATE::FARMING;
    QGraphicsEllipseItem *attack_area;
    QGraphicsEllipseItem *sight_area;

    void stateFarming();

};

#endif // ENEMY_H



