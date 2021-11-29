#include "Block.h"

/* The Block has no health regen by default */
Block::Block
    (const double& health, const double& max_health, const int& size, const int& vx, const int& vy, const double& xp, const int& level):
    GameEntity(health,0,max_health,size,vx,vy,xp,level) {}

GameEntity::CATEGORY Block::get_category() const {return GameEntity::CATEGORY::BLOCK;}
