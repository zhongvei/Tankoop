#include "Tank.h"
#include "Block.h"

#include <QDebug>

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
    }
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
