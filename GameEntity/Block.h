#ifndef BLOCK_H
#define BLOCK_H

#include "GameEntity.h"
#include <QGraphicsRectItem>

class Block : public GameEntity
{
public:
    Block(const double& health, const double& max_health,
          const int& size, const int& vx, const int& vy,
          const double& xp, const int&level);
    GameEntity::CATEGORY get_category() const override;
};

#endif // BLOCK_H
