#ifndef TANK_H
#define TANK_H
#include <QGraphicsRectItem>
#include "GameEntity.h"
#include <QRandomGenerator>
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <QtMath>

class Tank: public GameEntity, public QGraphicsRectItem {
public:

    double get_attack_speed() const;
    void set_attack_speed(double attack_speed);

    double get_bullet_speed() const;
    void set_bullet_speed(double bullet_speed);

    double get_damage() const;
    void set_damage(double damage); 

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    
private:
    double attack_speed;
    double bullet_speed;
    double damage;

    qreal angle = 0;
    qreal speed = 0;
    qreal mouseEyeDirection = 0;
    QColor color;

protected:
    Tank(
        const double& health, const double& health_regen, const double& max_health, 
        const int& size, const int& vx, const int& vy,const double& xp,
        const double& attack_speed,
        const double& bullet_speed,
        const double& damage,
        const int& level
    );

    void advance(int step) override;

};

//make all sub classes for the tank

#endif // TANK_H
