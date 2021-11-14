#ifndef TANK_H
#define TANK_H

#include "GameEntity.h"

class Tank: public GameEntity {
public:

    double get_attack_speed() const;
    void set_attack_speed(double attack_speed);

    double get_bullet_damage() const;
    void set_bullet_damage(double bullet_damage);

    double get_damage() const;
    void set_damage(double damage); 

    double get_reload_speed() const;
    void set_reload_speed(double reload_speed);

    int get_level() const;
    void set_level(int level);

private:
    double attack_speed;
    double bullet_speed;
    double damage;
    double reload_speed;
    int level;

protected:
    Tank(const double& attack_speed,
        const double& bullet_speed,
        const double& damage,
        const double& reload_speed,
        const int& level
    );
};

#endif // TANK_H
