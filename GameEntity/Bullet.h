#ifndef BULLET_H
#define BULLET_H

#include "Tank.h"
#include <QObject>
#include "GameEntity.h"
#include <QGraphicsRectItem>

class Bullet : public QObject, public QGraphicsRectItem, public GameEntity
{
    Q_OBJECT
public:        
    Bullet(Tank& tank, const double& damage, const double& degree, const int& size, const int& vx, const int& vy );
    double get_damage() const;
    double get_degree() const {return degree;};
    void set_degree (double degree) {this->degree = degree; return;};
    void isCollision();

private:
    double damage;
    double degree;
    Tank& tank;

public slots:
    void move();
};

#endif // BULLET_H
