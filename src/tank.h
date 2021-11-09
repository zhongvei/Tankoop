#ifndef TANK_H
#define TANK_H
#include <iostream>


class Tank
{
private:
    float health = 0.0f;
    float max_health = 0.0f;
    float attack_damage = 0.0f;
    float movement_speed = 0.0f;
    float attack_speed = 0.0f;
    float bullet_speed = 0.0f;
public:
    Tank(/* args */);
    ~Tank();
};

Tank::Tank(/* args */)
{
}

Tank::~Tank()
{
}


#endif