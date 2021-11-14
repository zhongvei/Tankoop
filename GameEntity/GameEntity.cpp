#include "GameEntity.h"

GameEntity::GameEntity(const double& health, const double& health_regen, const double& max_health,const int& size,const int& vx, const int& vy,const double& xp,const int& level):
health(health), health_regen(health_regen), max_health(max_health), alive(alive), size(size), vx(vx), vy(vy), xp(xp), level(level) {}

//accessor
double GameEntity::get_max_health() const {return max_health;}
double GameEntity::get_health() const {return health;}
double GameEntity::get_health_regen() const {return health_regen;}
bool GameEntity::get_alive() const {return alive;}
int GameEntity::get_size() const {return size;}
int GameEntity::get_vx() const {return vx;}
int GameEntity::get_vy() const {return vy;}
double GameEntity::get_xp() const {return xp;}
int GameEntity::get_level() const {return level;}

//mutator
void GameEntity::set_max_health(double max_health){
    this->max_health = max_health;
}
void GameEntity::set_health(double health) {
    this->health = health;
}
void GameEntity::set_health_regen(double health_regen) {
    this->health_regen = health_regen;
}
void GameEntity::set_alive(bool alive) {
    this->alive = alive;
}
void GameEntity::set_size(int size) {
    this->size = size;
}
void GameEntity::set_vx(int vx) {
    this->vx = vx;
}
void GameEntity::set_vy(int vy) {
    this->vy = vy;
}
void GameEntity::set_xp(double xp) {
    this->xp = xp;
}
void GameEntity::set_level(int level) {
    this->level = level;
}

