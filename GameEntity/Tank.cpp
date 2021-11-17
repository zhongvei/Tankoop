#include "Tank.h"

//constructor
Tank::Tank(
        const double& health, const double& health_regen, const double& max_health, const int& size,
        const int& vx, const int& vy,const double& xp,
        const double& attack_speed,
        const double& bullet_speed,
        const double& damage,
        const int& level,
        const int& skill_point):
        GameEntity(health,health_regen,max_health,size,vx,vy,xp,level), attack_speed(attack_speed), bullet_speed(bullet_speed), damage(damage) , skill_point(skill_point) {};

//accessor
double Tank::get_attack_speed() const {return attack_speed;}
double Tank::get_bullet_speed() const {return bullet_speed;}
double Tank::get_damage() const {return damage;}

//mutator
void Tank::set_attack_speed(double attack_speed) {
        this->attack_speed = attack_speed;
}
void Tank::set_bullet_speed(double bullet_speed) {
        this->bullet_speed = bullet_speed;
}
void Tank::set_damage(double damage) {
        this->damage = damage;
}