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
    Bullet(Tank& tank, const double& damage,const int& size, const int& vx, const int& vy);
    double get_damage() const;
    void isCollision();

private:
    double damage;
    Tank& tank;

public slots:
    void move();
};

#endif // BULLET_H
