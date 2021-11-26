#include "Tank.h"
#include "Block.h"

#include <QDebug>

class HealthBar;

/* The Constructor of Tank Object */
Tank::Tank(
        const double& health, const double& health_regen, const double& max_health, const int& size,
        const double& vx, const double& vy,const double& xp,
        const double& attack_speed,
        const double& bullet_speed,
        const double& damage,
        const int& level,
        const int& skill_point,
        const int& degree):
        GameEntity(health,health_regen,max_health,size,vx,vy,xp,level),
        attack_speed(attack_speed), bullet_speed(bullet_speed), damage(damage), skill_point(skill_point), degree(degree),
        color(QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256),
        QRandomGenerator::global()->bounded(256))
{};

/* The Accessor of Tank Object */
double Tank::get_attack_speed() const { return attack_speed;}
double Tank::get_bullet_speed() const { return bullet_speed; }
double Tank::get_damage() const { return damage; }
double Tank::get_degree() const { return degree; }
int Tank::get_skill_point() const {return skill_point;}
bool Tank::get_reload_status() const {return reload;}
int Tank::get_reload_finish() const {return reload_finish;}
int Tank::get_evolution_point() const {return evolution_point;}
HealthBar* Tank::get_health_bar() const {return health_bar;}

void Tank::advance(int step)
{
    if (!step)
        return;
}


/* Tank Graphics
 *
 * Functions below implements the drawing of the 'Tank' class and its subclasses
 * into the shape of a Tank, overriding QGraphicsItem::paint().
*/


/* boundingRect should be a large enough rectangle to fill the entire Tank. If tank exceeds
 * range of boundingRect, it will lead to drawing issues where parts of the Tank gets left
 * behind when Tank moves.
*/

QRectF Tank::boundingRect() const
{

//    return QRectF(-40, -40, 130, 130);
    return QRectF(0, 0, this->get_size(), this->get_size());
}

// overriding QGraphicsItem::paint(). Draws Tank instead of a Rectangle.
void Tank::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    //painter->drawRect(-12.5,-12.5,60,25);
    painter->drawRect(this->get_size()/2,this->get_size()/3,this->get_size()/2,this->get_size()/3);
    painter->setBrush(color);
    //painter->drawEllipse(-25, -25, 50, 50);
    painter->drawEllipse(this->get_size()*0.2, this->get_size()*0.2, this->get_size()*0.6, this->get_size()*0.6);
}

/* Reimplementing ::shape()
 * Collision detection handled by the Graphics View framework using shape-shape intersection.
 * Therefore we have to ensure that the QGraphicsItem::shape() function returns an accurate shape for our Tank.
*/
QPainterPath Tank::shape() const
{
    QPainterPath path;
    // Currently shape is just a small square. Change code if necessary for better collision detection.
    path.addEllipse(this->get_size()*0.2, this->get_size()*0.2, this->get_size()*0.6, this->get_size()*0.6);
//    path.addRect(-40, -40, 130, 130);
    return path;
}

//implementing the collision function
void Tank::check_collision() {
    QList<QGraphicsItem *> list = this->collidingItems();
    for(int i = 0; i < list.size();i++) {
        if((typeid(*list[i]) == typeid(Block))){
            qDebug()<<"HIT A BLOCK";
            delete list[i];
            this->set_health(this->get_health()-7);
            this->set_xp(this->get_xp() + 7);
        }
    }
}

void Tank::increase_level() {
    if((this->get_xp()/100 >= this->get_level())) {
       this->set_level(this->get_level() + 1);
       this->increase_total_skill_point();
       this->increase_skill_point();
       qDebug()<<"INCREASED LEVEL BY 1";
       if((this->get_level() % 10) == 0 && this->get_level() != 0) {
           this->increase_evolution_point();
           qDebug()<<"INCREASE EVOLUTION POINT BY 1";
       }
    }

}



void Tank::change_class(Tank::TYPE type) {
    this->type = type;
    switch (type)
    {
        case Tank::TYPE::GIANT:
            this->set_max_health(this->get_max_health() * 2);
            this->set_health_regen(this->get_health_regen() * 1.5);
            this->set_vx(this->get_vx() * 1);
            this->set_vy(this->get_vy() * 1);
            this->set_damage(this->get_damage() * 1.2);
            this->set_attack_speed(this->get_attack_speed() - 0.1);
            this->set_bullet_speed(this->get_bullet_speed() * 1);
            break;
        case Tank::TYPE::ASSASIN:
            this->set_max_health(this->get_max_health() * 1.2);
            this->set_health_regen(this->get_health_regen() * 0.8);
            this->set_vx(this->get_vx() * 1.5);
            this->set_vy(this->get_vy() * 1.5);
            this->set_damage(this->get_damage() * 1);
            this->set_attack_speed(this->get_attack_speed() - 0.2);
            this->set_bullet_speed(this->get_bullet_speed() * 1);
            break;
        case Tank::TYPE::SHARPSHOOTER:
            this->set_max_health(this->get_max_health() * 1);
            this->set_health_regen(this->get_health_regen() * 1);
            this->set_vx(this->get_vx() * 1.2);
            this->set_vy(this->get_vy() * 1.2);
            this->set_damage(this->get_damage() * 2);
            this->set_attack_speed(this->get_attack_speed() + 0.2);
            this->set_bullet_speed(this->get_bullet_speed() * 1.5);
            break;
        case Tank::TYPE::ENGINEER:
            this->set_max_health(this->get_max_health() * 1.5);
            this->set_health_regen(this->get_health_regen() * 1.2);
            this->set_vx(this->get_vx() * 1.2);
            this->set_vy(this->get_vy() * 1.2);
            this->set_damage(this->get_damage() * 1.2);
            this->set_attack_speed(this->get_attack_speed() - 0.1);
            this->set_bullet_speed(this->get_bullet_speed() * 1);
            break;
    }
}

void Tank::create_heatlh_bar(QGraphicsScene *scene) {
    health_bar = new HealthBar(this,scene);
}

/* The Mutator of Tank Object */
void Tank::set_attack_speed(double attack_speed) { this->attack_speed = attack_speed; }
void Tank::set_bullet_speed(double speed) { this->bullet_speed = speed; }
void Tank::set_damage(double damage) { this->damage = damage; }
void Tank::set_degree(double degree) { this->degree = degree; }
void Tank::increase_skill_point() {this->skill_point++; }
void Tank::decrease_skill_point() {this->skill_point--; }
int Tank::get_total_skill_point() const {return this->total_skill_point;}
void Tank::increase_total_skill_point() {this->total_skill_point++;}
void Tank::set_reload_finish(int reload_finish) {this->reload_finish = reload_finish;}
void Tank::change_reload_status() { reload? this->reload = 0: this->reload = 1;}
void Tank::increase_evolution_point() {this->evolution_point++;}
void Tank::decrease_evolution_point() {this->evolution_point--;}
