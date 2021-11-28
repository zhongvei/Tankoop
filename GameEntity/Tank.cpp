#include "Tank.h"
#include "Block.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Turret.h"

#include <QDebug>
#include <QTimer>

class HealthBar;

/* The Constructor of Tank Object */
Tank::Tank(
        const double& health, const double& health_regen, const double& max_health, const int& size,
        const double& vx, const double& vy,const double& xp,
        const double& reload_speed,
        const double& bullet_speed,
        const double& damage,
        const int& level,
        const int& skill_point,
        const int& degree):
        GameEntity(health,health_regen,max_health,size,vx,vy,xp,level),
        reload_speed(reload_speed), bullet_speed(bullet_speed), damage(damage), skill_point(skill_point), degree(degree),
        color(QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256),
        QRandomGenerator::global()->bounded(256))
{};

GameEntity::CATEGORY Tank::get_category() const {return  GameEntity::CATEGORY::TANK;}

/* The Accessor of Tank Object */
double Tank::get_reload_speed() const { return reload_speed;}
double Tank::get_bullet_speed() const { return bullet_speed; }
double Tank::get_damage() const { return damage; }
double Tank::get_degree() const { return degree; }
int Tank::get_skill_point() const {return skill_point;}
bool Tank::get_reload_status() const {return reload;}
int Tank::get_reload_finish() const {return reload_finish;}
int Tank::get_evolution_point() const {return evolution_point;}
HealthBar* Tank::get_health_bar() const {return health_bar;}
Tank::TYPE Tank::get_type() const {return type;}
Tank::SUBTANK Tank::get_subtank() const {return subtank;}
int Tank::get_sub_tank_evolution_point() const {return sub_tank_evolution_point;}
int Tank::get_cooldown() const {return cooldown;}
bool Tank::get_cooldown_status() const {return cooldown_status;}
double Tank::get_collision_damage() const {return collision_damage;}
bool Tank::get_skill_status() const {return skill_status;}

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
    QRectF square = QRectF(this->get_size()*0.2, this->get_size()*0.2, this->get_size()*0.6, this->get_size()*0.6);
    QPainterPath path;

    switch (get_type()) {    
        case Tank::TYPE::NORMAL:
            painter->drawRect(this->get_size()/2,this->get_size()/3,this->get_size()/2,this->get_size()/3);
            painter->setBrush(color);
            painter->drawEllipse(this->get_size()*0.2, this->get_size()*0.2, this->get_size()*0.6, this->get_size()*0.6);
            break;
        case Tank::TYPE::GIANT:
            switch(get_subtank()) {
                case Tank::SUBTANK::DEFAULT:
                    painter->drawRect(this->get_size()/2,this->get_size()/3,this->get_size()/2,this->get_size()/3);
                    painter->setBrush(color);
                    painter->drawRect(this->get_size()*0.2, this->get_size()*0.2, this->get_size()*0.6, this->get_size()*0.6);
                    break;
                case Tank::SUBTANK::POUNDER:
                    painter->drawRect(this->get_size()/2,this->get_size()/3,this->get_size()/2,this->get_size()/3);
                    painter->drawRect(0,this->get_size()/3,this->get_size()/2,this->get_size()/3);
                    painter->drawRect(this->get_size()/3,this->get_size()/2,this->get_size()/3,this->get_size()/2);
                    painter->drawRect(this->get_size()/3,0,this->get_size()/3,this->get_size()/2);
                    painter->setBrush(color);
                    painter->drawRect(this->get_size()*0.2, this->get_size()*0.2, this->get_size()*0.6, this->get_size()*0.6);
                    path.moveTo(this->get_size()/2,this->get_size()/2);
                    path.lineTo(this->get_size()*8/10, this->get_size()/2);
                    painter->drawPath(path);
                    break;
                case Tank::SUBTANK::SPINNER:
                    painter->drawRect(this->get_size()/2,this->get_size()/3,this->get_size()/2,this->get_size()/3);
                    path.moveTo(this->get_size()*2/5,this->get_size()/5);
                    path.lineTo(this->get_size()/2,0);
                    path.lineTo(this->get_size()*3/5,this->get_size()/5);
                    path.moveTo(this->get_size()*3/5,this->get_size()*4/5);
                    path.lineTo(this->get_size()/2,this->get_size());
                    path.lineTo(this->get_size()*2/5,this->get_size()*4/5);
                    path.moveTo(this->get_size()/5,this->get_size()*2/5);
                    path.lineTo(0,this->get_size()/2);
                    path.lineTo(this->get_size()/5,this->get_size()*3/5);
                    painter->drawPath(path);
                    painter->setBrush(color);
                    painter->drawRect(this->get_size()*0.2, this->get_size()*0.2, this->get_size()*0.6, this->get_size()*0.6);
                    break;
                default:
                    break;
            }
            break;
        case Tank::TYPE::ASSASSIN:
            switch(get_subtank()) {
                case Tank::SUBTANK::DEFAULT:
                    painter->drawRect(this->get_size()/2,this->get_size()*5/12,this->get_size()/2,this->get_size()/6);
                    path.moveTo(square.right(), square.top() + square.height()/2);
                    path.lineTo(square.bottomLeft());
                    path.lineTo(square.topLeft());
                    path.lineTo(square.right(), square.top() + square.height()/2);
                    painter->fillPath(path, color);
                    painter->drawPath(path);
                    break;
                case Tank::SUBTANK::HUNTER:
                    path.moveTo(square.left(),square.top());
                    path.lineTo(this->get_size(),this->get_size()/2);
                    path.lineTo(square.left(),square.bottom());
                    path.lineTo(this->get_size()/2,this->get_size()/2);
                    path.lineTo(square.left(),square.top());
                    painter->fillPath(path, color);
                    painter->drawPath(path);
                    break;
                case Tank::SUBTANK::IMMUNE:
                    painter->drawRect(this->get_size()*0.62,this->get_size()*5/12,this->get_size()*0.38,this->get_size()/6);
                    path.moveTo(square.right(), square.top() + square.height()/2);
                    path.lineTo(square.bottomLeft());
                    path.lineTo(square.topLeft());
                    path.lineTo(square.right(), square.top() + square.height()/2);
                    path.addEllipse(this->get_size()*0.4, this->get_size()*0.4, this->get_size()*0.2, this->get_size()*0.2);
                    painter->fillPath(path, color);
                    painter->drawPath(path);
                    break;
                default:
                    break;
            }

            break;
        case Tank::TYPE::SHARPSHOOTER:
            switch(get_subtank()) {
                case Tank::SUBTANK::DEFAULT:
                    painter->drawRect(this->get_size()/2,this->get_size()*5/12,this->get_size()/2,this->get_size()/6);
                    painter->setBrush(color);
                    painter->drawEllipse(this->get_size()*0.25, this->get_size()*0.25, this->get_size()*0.5, this->get_size()*0.5);
                    break;
                case Tank::SUBTANK::SNIPER:
                    painter->drawRect(this->get_size()*3/4,this->get_size()*5/12,this->get_size()/4,this->get_size()/6);
//                    path.arcMoveTo(square, 270);
//                    path.arcTo(square, 270, 180);
//                    path.arcMoveTo(this->get_size()*0.35, this->get_size()*0.2, this->get_size()*0.3, this->get_size()*0.6, 270);
//                    path.arcTo(this->get_size()*0.35, this->get_size()*0.2, this->get_size()*0.3, this->get_size()*0.6, 270, 180);
                    path.arcMoveTo(-this->get_size()*0.6, this->get_size()*0.2, this->get_size()*1.4, this->get_size()*0.6, 270);
                    path.arcTo(-this->get_size()*0.6, this->get_size()*0.2, this->get_size()*1.4, this->get_size()*0.6, 270, 180);
                    path.arcMoveTo(-this->get_size()*0.35, this->get_size()*0.2, this->get_size()*0.9, this->get_size()*0.6, 270);
                    path.arcTo(-this->get_size()*0.35, this->get_size()*0.2, this->get_size()*0.9, this->get_size()*0.6, 270, 180);
                    painter->fillPath(path, color);
                    painter->drawPath(path);
                    break;
                case Tank::SUBTANK::DUAL:
                    painter->drawRect(this->get_size()/2,this->get_size()/4,this->get_size()*4/9,this->get_size()/2);
                    painter->drawRect(this->get_size()/2,this->get_size()*5/12,this->get_size()/2,this->get_size()/6);
                    painter->setBrush(color);
                    painter->drawEllipse(this->get_size()*0.25, this->get_size()*0.25, this->get_size()*0.5, this->get_size()*0.5);
                    break;
                default:
                    break;
            }

            break;
        case Tank::TYPE::ENGINEER:
            switch(get_subtank()) {
                case Tank::SUBTANK::DEFAULT:
                    painter->drawRect(this->get_size()/2,this->get_size()*5/12,this->get_size()/2,this->get_size()/6);
                    path.moveTo(square.left() + square.width()*tan(60), square.top());
                    path.lineTo(square.right() - square.width()*tan(60), square.top());
                    path.lineTo(square.right(), square.top() + square.height()/2);
                    path.lineTo(square.right() - square.width()*tan(60), square.bottom());
                    path.lineTo(square.left() + square.width()*tan(60), square.bottom());
                    path.lineTo(square.left(), square.top() + square.height()/2);
                    path.lineTo(square.left() + square.width()*tan(60), square.top());
                    painter->fillPath(path, color);
                    painter->drawPath(path);
                    break;
                case Tank::SUBTANK::SPAWNER:
                    painter->drawRect(this->get_size()/2,this->get_size()*5/12,this->get_size()/2,this->get_size()/6);
                    path.moveTo(square.left() + square.width()*2*tan(60), square.top());
                    path.lineTo(square.right() - square.width()*2*tan(60), square.top());
                    path.lineTo(square.right(), square.top() + square.height()/2);
                    path.lineTo(square.right() - square.width()*2*tan(60), square.bottom());
                    path.lineTo(square.left() + square.width()*2*tan(60), square.bottom());
                    path.lineTo(square.left(), square.top() + square.height()/2);
                    path.lineTo(square.left() + square.width()*2*tan(60), square.top());
                    painter->fillPath(path, color);
                    painter->drawPath(path);
                    break;
                case Tank::SUBTANK::TRAPPER:
                    painter->drawRect(this->get_size()/2,this->get_size()*5/12,this->get_size()/2,this->get_size()/6);
                    path.moveTo(square.left() - square.width()*tan(60), square.top());
                    path.lineTo(square.right() + square.width()*tan(60), square.top());
                    path.lineTo(square.right(), square.top() + square.height()/2);
                    path.lineTo(square.right() + square.width()*tan(60), square.bottom());
                    path.lineTo(square.left() - square.width()*tan(60), square.bottom());
                    path.lineTo(square.left(), square.top() + square.height()/2);
                    path.lineTo(square.left() - square.width()*tan(60), square.top());
                    painter->fillPath(path, color);
                    painter->drawPath(path);
                    break;
                default:
                    break;
            }
            break;
    }
}

/* Reimplementing ::shape()
 * Collision detection handled by the Graphics View framework using shape-shape intersection.
 * Therefore we have to ensure that the QGraphicsItem::shape() function returns an accurate shape for our Tank.
*/
QPainterPath Tank::shape() const
{
    QRectF square = QRectF(this->get_size()*0.2, this->get_size()*0.2, this->get_size()*0.6, this->get_size()*0.6);
    QPainterPath path;
    // Shape for collision detection
    switch (get_type()) {
        case Tank::TYPE::NORMAL:
            path.addEllipse(this->get_size()*0.2, this->get_size()*0.2, this->get_size()*0.6, this->get_size()*0.6);
            break;
        case Tank::TYPE::GIANT:
            path.addRect(this->get_size()*0.2, this->get_size()*0.2, this->get_size()*0.6, this->get_size()*0.6);
            break;
        case Tank::TYPE::ASSASSIN:
            switch(get_subtank()) {
                case Tank::SUBTANK::DEFAULT:
                    path.moveTo(square.right(), square.top() + square.height()/2);
                    path.lineTo(square.bottomLeft());
                    path.lineTo(square.topLeft());
                    path.lineTo(square.right(), square.top() + square.height()/2);
                    break;
                case Tank::SUBTANK::HUNTER:
                    path.moveTo(square.left(),square.top());
                    path.lineTo(this->get_size(),this->get_size()/2);
                    path.lineTo(square.left(),square.bottom());
                    path.lineTo(this->get_size()/2,this->get_size()/2);
                    path.lineTo(square.left(),square.top());
                    break;
                case Tank::SUBTANK::IMMUNE:
                    path.moveTo(square.right(), square.top() + square.height()/2);
                    path.lineTo(square.bottomLeft());
                    path.lineTo(square.topLeft());
                    path.lineTo(square.right(), square.top() + square.height()/2);
                    break;
                default:
                    break;
            }

            break;
        case Tank::TYPE::SHARPSHOOTER:
            switch(get_subtank()) {
                case Tank::SUBTANK::DEFAULT:
                    path.addEllipse(this->get_size()*0.25, this->get_size()*0.25, this->get_size()*0.5, this->get_size()*0.5);
                    break;
                case Tank::SUBTANK::SNIPER:
                    path.arcMoveTo(-this->get_size()*0.6, this->get_size()*0.2, this->get_size()*1.4, this->get_size()*0.6, 270);
                    path.arcTo(-this->get_size()*0.6, this->get_size()*0.2, this->get_size()*1.4, this->get_size()*0.6, 270, 180);
                    path.arcMoveTo(-this->get_size()*0.35, this->get_size()*0.2, this->get_size()*0.9, this->get_size()*0.6, 270);
                    path.arcTo(-this->get_size()*0.35, this->get_size()*0.2, this->get_size()*0.9, this->get_size()*0.6, 270, 180);
                    break;
                case Tank::SUBTANK::DUAL:
                    path.addEllipse(this->get_size()*0.25, this->get_size()*0.25, this->get_size()*0.5, this->get_size()*0.5);
                    break;
                default:
                    break;
            }

            break;
        case Tank::TYPE::ENGINEER:
        switch(get_subtank()) {
            case Tank::SUBTANK::DEFAULT:
                path.moveTo(square.left() + square.width()*tan(60), square.top());
                path.lineTo(square.right() - square.width()*tan(60), square.top());
                path.lineTo(square.right(), square.top() + square.height()/2);
                path.lineTo(square.right() - square.width()*tan(60), square.bottom());
                path.lineTo(square.left() + square.width()*tan(60), square.bottom());
                path.lineTo(square.left(), square.top() + square.height()/2);
                path.lineTo(square.left() + square.width()*tan(60), square.top());
                break;
            case Tank::SUBTANK::SPAWNER:
                path.moveTo(square.left() + square.width()*2*tan(60), square.top());
                path.lineTo(square.right() - square.width()*2*tan(60), square.top());
                path.lineTo(square.right(), square.top() + square.height()/2);
                path.lineTo(square.right() - square.width()*2*tan(60), square.bottom());
                path.lineTo(square.left() + square.width()*2*tan(60), square.bottom());
                path.lineTo(square.left(), square.top() + square.height()/2);
                path.lineTo(square.left() + square.width()*2*tan(60), square.top());
                break;
            case Tank::SUBTANK::TRAPPER:
                path.moveTo(square.left() - square.width()*tan(60), square.top());
                path.lineTo(square.right() + square.width()*tan(60), square.top());
                path.lineTo(square.right(), square.top() + square.height()/2);
                path.lineTo(square.right() + square.width()*tan(60), square.bottom());
                path.lineTo(square.left() - square.width()*tan(60), square.bottom());
                path.lineTo(square.left(), square.top() + square.height()/2);
                path.lineTo(square.left() - square.width()*tan(60), square.top());
                break;
            default:
                break;
        }

            break;
    }
    return path;
}

//implementing the collision function
void Tank::check_collision() {
    QList<QGraphicsItem *> list = this->collidingItems();
    for(int i = 0; i < list.size();i++) {
        GameEntity* the_thing = dynamic_cast<GameEntity*>(list[i]);
        if(the_thing != nullptr && the_thing->get_category() == GameEntity::CATEGORY::BLOCK){
            Block* the_block= dynamic_cast<Block*>(list[i]);
            this->set_health(this->get_health() - get_collision_damage());
            this->set_xp(this->get_xp() + the_block->get_xp()*0.7); //only gets 70% of the exp
            delete the_block;
        }else if(the_thing != nullptr && the_thing->get_class() == GameEntity::CLASS::ENEMY && get_subtank() == Tank::SUBTANK::SPINNER && get_skill_status()) {
            Enemy* the_enemy= dynamic_cast<Enemy*>(list[i]);
            the_enemy->set_health(the_enemy->get_health() - 10);
            if(the_enemy->get_health() <= 0){
               scene()->removeItem(the_enemy->get_health_bar());
               this->set_xp(this->get_xp() + the_enemy->get_xp());
               delete the_enemy;
            }
        }
    }
}

void Tank::increase_level() {
    if((this->get_xp()/100 >= this->get_level())) {
       this->set_level(this->get_level() + 1);
       this->increase_total_skill_point();
       this->increase_skill_point();
       this->set_size(this->get_size()*1.03);
    //    qDebug()<<"INCREASED LEVEL BY 1";
       if(this->get_level() == 5) {
           this->increase_evolution_point();
        //    qDebug()<<"INCREASE EVOLUTION POINT BY 1";
       }
       if(this->get_level() == 10) {
           this->increase_sub_tank_evolution_point();
        //    qDebug()<<"INCREASE SUBTANK EVOLUTION POINT";
       }
    }

}

void Tank::skill() {
    if(!this->get_cooldown_status()) {
        qDebug()<<"skill pressed";
        change_skill_status();
        if(this->get_subtank() == Tank::SUBTANK::SPINNER) {
            this->set_vx(this->get_vx() * 1.5);
            this->set_vy(this->get_vy() * 1.5);
            QTimer::singleShot(4000,[=](){skill_timer_timeout();});
            return;
        } else if (this->get_subtank() == Tank::SUBTANK::POUNDER) {
            QTimer::singleShot(5000,[=](){skill_timer_timeout();});
            return;
        } else if (this->get_subtank() == Tank::SUBTANK::HUNTER) {
            this->set_vx(this->get_vx() * 1.2);
            this->set_vy(this->get_vy() * 1.2);
            this->set_damage(this->get_damage() * 1.5);
            this->set_reload_speed(this->get_reload_speed() - 0.2);
            this->set_bullet_speed(this->get_bullet_speed() * 1.5);
            QTimer::singleShot(5000,[=](){skill_timer_timeout();});
            return;
        } else if (this->get_subtank() == Tank::SUBTANK::IMMUNE) {
            this->set_vx(this->get_vx() * 1.5);
            this->set_vy(this->get_vy() * 1.5);
            this->set_collision_damage(0);
            this->set_health_regen(this->get_health_regen() + 5);
            QTimer::singleShot(3000,[=](){skill_timer_timeout();});
            return;
        } else if (this->get_subtank() == Tank::SUBTANK::SNIPER) {
            this->set_damage(this->get_damage() * 3);
            this->set_bullet_speed(this->get_bullet_speed() * 3);
            QTimer::singleShot(3000,[=](){skill_timer_timeout();});
            return;
        } else if (this->get_subtank() == Tank::SUBTANK::DUAL) {
            QTimer::singleShot(4000,[=](){skill_timer_timeout();});
            return;
        } else if (this->get_subtank() == Tank::SUBTANK::SPAWNER) {

            turret = new Turret(500,100,this); // multiple of 50
            turret->setPos(x(),y());
            turret->setRect(0,0,turret->get_size(),turret->get_size());
            turret->get_attack_area()->setPos(turret->x() - turret->get_size() * (turret->get_attack_scale()-1)/2,
                                             turret->y() - turret->get_size() * (turret->get_attack_scale()-1)/2);
            scene()->addItem(turret);
            scene()->addItem(turret->get_attack_area());
            QTimer::singleShot(4000,[=](){skill_timer_timeout();});
            return;
        } else if (this->get_subtank() == Tank::SUBTANK::TRAPPER) {
            return;
        }
    }
}

void Tank::skill_timer_timeout() {
    change_skill_status();
    switch(this->get_subtank())
    {
        case Tank::SUBTANK::DEFAULT:
            break;
        case Tank::SUBTANK::SPINNER:
            this->set_vx(this->get_vx() / 1.5);
            this->set_vy(this->get_vy() / 1.5);
            break;
        case Tank::SUBTANK::POUNDER:
            break;
        case Tank::SUBTANK::HUNTER:
            this->set_vx(this->get_vx() / 1.2);
            this->set_vy(this->get_vy() / 1.2);
            this->set_damage(this->get_damage() / 1.5);
            this->set_reload_speed(this->get_reload_speed() + 0.2);
            this->set_bullet_speed(this->get_bullet_speed() / 1.5);
            break;
        case Tank::SUBTANK::IMMUNE:
            this->set_vx(this->get_vx() / 1.5);
            this->set_vy(this->get_vy() / 1.5);
            this->set_health_regen(this->get_health_regen() - 5);
            this->set_collision_damage(7);
            break;
        case Tank::SUBTANK::SNIPER:
            this->set_damage(this->get_damage() / 3);
            this->set_bullet_speed(this->get_bullet_speed() / 3);
            break;
        case Tank::SUBTANK::DUAL:
            break;
        case Tank::SUBTANK::SPAWNER:
            delete turret;
            break;
        case Tank::SUBTANK::TRAPPER:
            break;
    }
}

void Tank::change_class(Tank::TYPE type) {
    this->type = type;
    switch (type)
    {
        case Tank::TYPE::NORMAL:
            break;
        case Tank::TYPE::GIANT:
            this->set_size(this->get_size()*1.2);
            this->set_max_health(this->get_max_health() * 2);
            this->set_health_regen(this->get_health_regen() * 1.5);
            this->set_vx(this->get_vx() * 1);
            this->set_vy(this->get_vy() * 1);
            this->set_damage(this->get_damage() * 1.2);
            this->set_reload_speed(this->get_reload_speed() - 0.1);
            this->set_bullet_speed(this->get_bullet_speed() * 1);
            break;
        case Tank::TYPE::ASSASSIN:
            this->set_size(this->get_size()*1.2);
            this->set_max_health(this->get_max_health() * 1.2);
            this->set_health_regen(this->get_health_regen() * 0.8);
            this->set_vx(this->get_vx() * 1.5);
            this->set_vy(this->get_vy() * 1.5);
            this->set_damage(this->get_damage() * 1);
            this->set_reload_speed(this->get_reload_speed() - 0.2);
            this->set_bullet_speed(this->get_bullet_speed() * 1);
            break;
        case Tank::TYPE::SHARPSHOOTER:
            this->set_size(this->get_size() * 1);
            this->set_max_health(this->get_max_health() * 1);
            this->set_health_regen(this->get_health_regen() * 1);
            this->set_vx(this->get_vx() * 1.2);
            this->set_vy(this->get_vy() * 1.2);
            this->set_damage(this->get_damage() * 2);
            this->set_reload_speed(this->get_reload_speed() + 0.2);
            this->set_bullet_speed(this->get_bullet_speed() * 1.5);
            break;
        case Tank::TYPE::ENGINEER:
            this->set_size(this->get_size()*1.1);
            this->set_max_health(this->get_max_health() * 1.5);
            this->set_health_regen(this->get_health_regen() * 1.2);
            this->set_vx(this->get_vx() * 1.2);
            this->set_vy(this->get_vy() * 1.2);
            this->set_damage(this->get_damage() * 1.2);
            this->set_reload_speed(this->get_reload_speed() - 0.1);
            this->set_bullet_speed(this->get_bullet_speed() * 1);
            break;
    }
    this->set_health(this->get_max_health());
}


void Tank::change_subtank(Tank::SUBTANK subtank) {
    this->subtank = subtank;
    switch (subtank)
    {
        case Tank::SUBTANK::DEFAULT:
            break;
        case Tank::SUBTANK::SPINNER:
            break;
        case Tank::SUBTANK::POUNDER:
            break;
        case Tank::SUBTANK::HUNTER:
            break;
        case Tank::SUBTANK::IMMUNE:
            break;
        case Tank::SUBTANK::SNIPER:
            break;
        case Tank::SUBTANK::DUAL:
            break;
        case Tank::SUBTANK::SPAWNER:
            break;
        case Tank::SUBTANK::TRAPPER:
            break;
    }

}

void Tank::create_heatlh_bar(QGraphicsScene *scene) {
    health_bar = new HealthBar(this,scene);
}
/*
        const double& health, const double& health_regen, const double& max_health, const int& size,
        const double& vx, const double& vy,const double& xp,
        const double& reload_speed,
        const double& bullet_speed,
        const double& damage,
        const int& level,
        const int& skill_point,
        const int& degree
*/
Tank& Tank::operator=(const Tank &tank){
    //    this->set_health(tank.get_health());
    //    this->set_health_regen(tank.get_health_regen());
    //    this->set_max_health(tank.get_max_health());
    //    this->set_size(tank.get_size());
    //    this->set_vx(tank.get_vx());
    //    this->set_vy(tank.get_vy());
    //    this->set_xp(tank.get_xp());
    qDebug() << "CALLING COPY CONSTRUCTOR";
    this->set_reload_speed(tank.get_reload_speed());
    this->set_bullet_speed(tank.get_bullet_speed());
    this->set_damage(tank.get_damage());
    this->set_skill_point(tank.get_skill_point());
    this->set_degree(tank.get_degree());

    return *this;
}
//health,health_regen,max_health,size,vx,vy,xp,level
Tank::Tank(const Tank& tank):GameEntity(tank.get_health(),tank.get_health_regen(),tank.get_max_health(),tank.get_size(),tank.get_vx(),tank.get_vy(),tank.get_xp(),tank.get_level()){
    *this = tank;
}

/* The Mutator of Tank Object */
void Tank::set_reload_speed(double reload_speed) { this->reload_speed = reload_speed; }
void Tank::set_bullet_speed(double speed) { this->bullet_speed = speed; }
void Tank::set_skill_point(int skill_point){ this->skill_point = skill_point; }
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
void Tank::increase_sub_tank_evolution_point() {this->sub_tank_evolution_point++;}
void Tank::decrease_sub_tank_evolution_point() {this->sub_tank_evolution_point--;}
void Tank::change_cooldown_status() {this->cooldown_status? this->cooldown_status = false: this->cooldown_status = true;}
void Tank::set_cooldown(int cooldown) {this->cooldown = cooldown;}
void Tank::set_collision_damage(double collision_damage) {this->collision_damage = collision_damage;}
void Tank::change_skill_status() {this->skill_status? this->skill_status = false: this->skill_status = true;}
