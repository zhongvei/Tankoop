#include "Block.h"

//block doesnt have health_regen and is always spawn as alive
Block::Block
    (const double& health, const double& max_health, const int& size, const int& vx, const int& vy, const double& xp, const double& collision_damage): 
    GameEntity(health,0,max_health,size,vx,vy,xp), collision_damage(collision_damage) {}

