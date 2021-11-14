#include "Tank.h"

Tank::Tank(
        const double& health, const double& health_regen, const double& max_health, const int& size,
        const int& vx, const int& vy,const double& xp,
        const double& attack_speed,
        const double& bullet_speed,
        const double& damage,
        const int& level):
        GameEntity(health,health_regen,max_health,size,vx,vy,xp), attack_speed(attack_speed), bullet_speed(bullet_speed), damage(damage), level(level) {};
