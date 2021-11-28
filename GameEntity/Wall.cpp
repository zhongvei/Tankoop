#include "Wall.h"
#include <QTransform>

Wall::Wall(const double& degree): GameEntity(100,0,100,100,0,0,0,0), degree(degree)
{
    setRect(0,0,10,this->get_size());
}

double Wall::get_degree() const { return degree; }

GameEntity::CATEGORY Wall::get_category() const {return GameEntity::CATEGORY::WALL;}
