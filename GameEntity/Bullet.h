#ifndef BULLET_H
#define BULLET_H

#include "Tank.h"
#include "GameEntity.h"

class Bullet : public GameEntity
{
public:
    Bullet(Tank& tank, const double& damage);
    double get_damage() const;

private:
    double damage;
    Tank* tank;

};

#endif // BULLET_H
