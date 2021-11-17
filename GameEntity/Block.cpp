#include "Block.h"

//block doesnt have health_regen and is always spawn as alive
Block::Block
    (const double& health, const double& max_health, const int& size, const int& vx, const int& vy, const double& xp, const int& level ,const double& collision_damage): 
    GameEntity(health,0,max_health,size,vx,vy,xp,level), collision_damage(collision_damage) {}

/* The Acessor of Block Object */
double Block::get_collision_damge() const {return collision_damage;}

/* The Mutator of Block Object */
void Block::set_collision_damage(double collision_damage) {
    this->collision_damage = collision_damage;
} 
