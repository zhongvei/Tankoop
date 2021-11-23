#include "Tank.h"
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
        GameEntity(health,health_regen,max_health,size,vx,vy,xp,level), attack_speed(attack_speed), bullet_speed(bullet_speed), damage(damage), skill_point(skill_point), degree(degree),
         color(QRandomGenerator::global()->bounded(256),
                                           QRandomGenerator::global()->bounded(256),
                                           QRandomGenerator::global()->bounded(256))    {};

/* The Accessor of Tank Object */
double Tank::get_attack_speed() const { return attack_speed;}
double Tank::get_bullet_speed() const { return bullet_speed; }
double Tank::get_damage() const { return damage; }
double Tank::get_degree() const { return degree; }
int Tank::get_skill_point() const {return skill_point;}


void Tank::advance(int step)
{
    if (!step)
        return;
    //qDebug("Tank Advance");
    QPointF healthpos;
    healthpos.setX(this->x());
    healthpos.setY(this->y());
    //qDebug() << healthpos;
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
    return QRectF(-65, -65, 130, 130);
}

// overriding QGraphicsItem::paint(). Draws Tank instead of a Rectangle.
void Tank::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawRect(-12.5,-12.5,25,60);
    painter->setBrush(color);
    painter->drawEllipse(-25, -25, 50, 50);
}

/* Reimplementing ::shape()
 * Collision detection handled by the Graphics View framework using shape-shape intersection.
 * Therefore we have to ensure that the QGraphicsItem::shape() function returns an accurate shape for our Tank.
*/
QPainterPath Tank::shape() const
{
    QPainterPath path;
    // Currently shape is just a small square. Change code if necessary for better collision detection.
    path.addRect(-40, -40, 80, 80);
//    path.addRect(-40, -40, 130, 130);
    return path;
}
/* The Mutator of Tank Object */
void Tank::set_attack_speed(double attack_speed) { this->attack_speed = attack_speed; }
void Tank::set_bullet_speed(double speed) { this->bullet_speed = speed; }
void Tank::set_damage(double damage) { this->damage = damage; }
void Tank::set_degree(double degree) { this->degree = degree; }
void Tank::increase_skill_point() {this->skill_point++; }
void Tank::decrease_skill_point() {this->skill_point--; }
