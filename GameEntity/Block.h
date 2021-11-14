#ifndef BLOCK_H
#define BLOCK_H

#include "GameEntity.h"

class Block : public GameEntity 
{
public:
    double get_collision_damge() const;
    void set_collision_damage(double collision_damage);

protected:
    Block(const double& health, const double& max_health, const int& size, const int& vx, const int& vy, const double& xp, const double& collision_damage);
private:
    double collision_damage {};
};

#endif // BLOCK_H
