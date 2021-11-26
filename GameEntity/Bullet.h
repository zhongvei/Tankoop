#ifndef BULLET_H
#define BULLET_H

#include "Tank.h"
#include "GameEntity.h"
#include <QObject>


class Bullet : public QObject, public GameEntity
{
    Q_OBJECT
public:        
    Bullet(Tank* tank, const double& damage, const double& degree, const int& size, const double& vx, const double& vy );
    double get_damage() const;
    double get_degree() const {return degree;}
    void set_degree (double degree) {this->degree = degree;}

private:
    double damage;
    double degree;
    Tank* tank;

public slots:
    void move();
};

#endif // BULLET_H
