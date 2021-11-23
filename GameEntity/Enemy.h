#ifndef ENEMY_H
#define ENEMY_H

#include "Tank.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <QPointF>
#include <QObject>

class Enemy: public QObject, public QTransform, public Tank
{
    Q_OBJECT
public:
    Enemy(double attack_range,const int& size);
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



