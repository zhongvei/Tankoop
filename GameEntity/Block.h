#ifndef BLOCK_H
#define BLOCK_H

#include "GameEntity.h"
#include <QGraphicsRectItem>

class Block : public GameEntity
{
public:
    /*
    *  @funct:  constructor for the Block
    *  @param:  health: the health for the Block, max_health: the max_health for the Block, size: the size for the Block
    *  @param:  vx: the movement speed in the x axis for the Block, vy: the movement speed in the y axis for the Block
    *  @param:  xp: the experience point for the Block, level: the level for the Block
    *  @return: N/A     
    */
    Block(const double& health, const double& max_health,
          const int& size, const int& vx, const int& vy,
          const double& xp, const int&level);

    /*
    *  @funct:  default the destructor for the Block to improve readebility
    *  @param:  N/A
    *  @return: N/A     
    */      
    ~Block() = default;
    
    /*
    *  @funct:  get the GameEntity category type, which is GameEntity::CATEGORY::BLOCK in this case
    *  @param:  N/A
    *  @return: GameEntitiy::CATEGORY: the GameEntity category type, which is GameEntity::CATEGORY::BLOCK in this case
    */
    GameEntity::CATEGORY get_category() const override;
};

#endif // BLOCK_H
