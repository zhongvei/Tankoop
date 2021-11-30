#ifndef WALL_H
#define WALL_H

#include "GameEntity.h"

#include <cmath>

class Wall: public GameEntity
{
public:
    /*
    *  @funct:  the constructor for the Wall
    *
    *  @param:  degree: the angle which the Healthbar is spawn on
    *  @return: N/A
    */
    Wall(const double& degree);

    /*
    *  @funct:  the destructor for the Wall
    *
    *  @param:  N/A
    *  @return: N/A
    */
    ~Wall() = default;

    /*
    *  @funct:  get the GameEntity category, which is GameEntity::CATEGORY::WALLin this case
    *  @param:  N/A
    *  @return: GameEntitiy::CATEGORY: the GameEntity category, which is GameEntity::CATEGORY::WALL in this case
    */
    GameEntity::CATEGORY get_category() const override;
};

#endif // WALL_H
