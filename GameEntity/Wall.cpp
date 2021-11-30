#include "Wall.h"
#include <QTransform>

//the constructor for Wall
Wall::Wall(const double& degree): GameEntity(100,0,100,100,0,0,0,0)
{
    setRect(0,0,10,this->get_size());
    QTransform transform;
    transform.translate(10/2,this->get_size()/2);
    transform.rotate(degree);
    transform.translate(-(10/2),-(this->get_size()/2));
    setTransform(transform);
}

GameEntity::CATEGORY Wall::get_category() const {return GameEntity::CATEGORY::WALL;}
