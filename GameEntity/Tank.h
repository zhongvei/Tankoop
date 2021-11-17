#ifndef TANK_H
#define TANK_H

#include "GameEntity.h"

class Tank: public GameEntity {
public:

    inline double get_attack_speed() const;
    inline void set_attack_speed(double attack_speed);

    inline double get_bullet_speed() const;
    inline void set_bullet_speed(double bullet_speed);

    inline double get_damage() const;
    inline void set_damage(double damage); 
    
private:
    double attack_speed;
    double bullet_speed;
    double damage;
    int skill_point;

protected:
    Tank(
        const double& health, const double& health_regen, const double& max_health, 
        const int& size, const int& vx, const int& vy,const double& xp,
        const double& attack_speed,
        const double& bullet_speed,
        const double& damage,
        const int& level,
        const int& skill_point
    );
};

//make all sub classes for the tank

#endif // TANK_H
