#include "GameEntity.h"

/* The constructor of the GameEntity */
GameEntity::GameEntity(const double& health, const double& health_regen, const double& max_health,
                       const int& size,const double& vx, const double& vy,const double& xp,const int& level) :
                       max_health(max_health), health(health), health_regen(health_regen),
                       size(size), vx(vx), vy(vy), xp(xp), level(level) {}

/* The Accessor of GameEntity Obeject */
double GameEntity::get_max_health() const { return max_health; }
double GameEntity::get_health() const { return health; }
double GameEntity::get_health_regen() const { return health_regen; }
double GameEntity::get_xp() const { return xp; }
int GameEntity::get_size() const { return size; }
double GameEntity::get_vx() const { return vx; }
double GameEntity::get_vy() const { return vy; }
int GameEntity::get_level() const { return level; }

/* The Mutator of GameEntity Obeject */
void GameEntity::set_max_health(double max_health){ this->max_health = max_health;}
void GameEntity::set_health(double health) { this->health = health;}
void GameEntity::set_health_regen(double health_regen) { this->health_regen = health_regen;}
void GameEntity::set_size(int size) { this->size = size;}
void GameEntity::set_vx(double vx) { this->vx = vx;}
void GameEntity::set_vy(double vy) { this->vy = vy;}
void GameEntity::set_xp(double xp) { this->xp = xp;}
void GameEntity::set_level(int level) { this->level = level;}

/* Default virtual function */
GameEntity::CLASS GameEntity::get_class() const {return GameEntity::CLASS::NONE;}
