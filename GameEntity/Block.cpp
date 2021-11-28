#include "Block.h"
#include <QDebug>

//block doesnt have health_regen and is always spawn as alive
Block::Block
    (const double& health, const double& max_health, const int& size, const int& vx, const int& vy, const double& xp, const int& level):
    GameEntity(health,0,max_health,size,vx,vy,xp,level) {}

GameEntity::CATEGORY Block::get_category() const {return GameEntity::CATEGORY::BLOCK;}
