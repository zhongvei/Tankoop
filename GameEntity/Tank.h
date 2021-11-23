#ifndef TANK_H
#define TANK_H

#include "GameEntity.h"
#include <QGraphicsRectItem>

#include "math.h"

class Tank: public GameEntity, public QGraphicsRectItem {
public:

    double get_attack_speed() const;
    void set_attack_speed(double attack_speed);

    double get_bullet_speed() const;
    void set_bullet_speed(double bullet_speed);

    double get_damage() const;
    void set_damage(double damage); 

    double get_degree() const;
    void set_degree(double degree);

    int get_skill_point() const;
    void increase_skill_point();
    void decrease_skill_point();
    
private:
    double attack_speed{};
    double bullet_speed{};
    double damage{};
    int skill_point{};
    double degree{};

protected:
    Tank(
        const double& health, const double& health_regen, const double& max_health, 
        const int& size, const double& vx, const double& vy,const double& xp,
        const double& attack_speed,
        const double& bullet_speed,
        const double& damage,
        const int& level,
        const int& skill_point,
        const int& degree
    );
};

//make all sub classes for the tank

#endif // TANK_H
