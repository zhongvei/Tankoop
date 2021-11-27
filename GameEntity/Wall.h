#ifndef WALL_H
#define WALL_H

#include "GameEntity.h"

#include <cmath>

class Wall: public GameEntity
{
public:
    Wall(const double& degree);
    double get_degree() const;
private:
    double degree{};
};

#endif // WALL_H
