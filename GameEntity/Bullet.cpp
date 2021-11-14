#include "Bullet.h"

//bullet has no health, max health, health_regen and xp
Bullet::Bullet(Tank& tank, const double& damage,const int& size, const int& vx, const int& vy): 
    tank(tank), GameEntity(0,0,0,size,vx,vy,0) {}