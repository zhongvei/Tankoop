#include "Tank.h"
#include "Block.h"
#include "Bullet.h"
#include "Enemy.h"

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
Tank::TYPE Tank::get_class() const {return type;}
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
    QRectF rectangle = QRectF(this->get_size()*0.2, this->get_size()*0.2, this->get_size()*0.6, this->get_size()*0.6);
    QPainterPath path;

    switch (get_class()) {    
        case Tank::TYPE::NORMAL:
           painter->drawRect(this->get_size()/2,this->get_size()/3,this->get_size()/2,this->get_size()/3);
            painter->setBrush(color);
            painter->drawEllipse(this->get_size()*0.2, this->get_size()*0.2, this->get_size()*0.6, this->get_size()*0.6);
            break;
        case Tank::TYPE::GIANT:
            painter->drawRect(this->get_size()/2,this->get_size()/3,this->get_size()/2,this->get_size()/3);
            painter->setBrush(color);
            painter->drawRect(this->get_size()*0.2, this->get_size()*0.2, this->get_size()*0.6, this->get_size()*0.6);
            break;
        case Tank::TYPE::ASSASSIN:
            painter->drawRect(this->get_size()/2,this->get_size()*5/12,this->get_size()/2,this->get_size()/6);
            path.moveTo(rectangle.right(), rectangle.top() + rectangle.height()/2);
            path.lineTo(rectangle.bottomLeft());
            path.lineTo(rectangle.topLeft());
            path.lineTo(rectangle.right(), rectangle.top() + rectangle.height()/2);
            painter->fillPath(path, color);
            break;
        case Tank::TYPE::SHARPSHOOTER:
            painter->drawRect(this->get_size()/2,this->get_size()*5/12,this->get_size()/2,this->get_size()/6);
            painter->setBrush(color);
            painter->drawEllipse(this->get_size()*0.25, this->get_size()*0.25, this->get_size()*0.5, this->get_size()*0.5);
            break;
        case Tank::TYPE::ENGINEER:
            painter->drawRect(this->get_size()/2,this->get_size()*5/12,this->get_size()/2,this->get_size()/6);
            painter->setPen (QPen(Qt::black, 5, Qt::SolidLine));
            path.moveTo(rectangle.left() + rectangle.width()*2*tan(60), rectangle.top());
            path.lineTo(rectangle.right() - rectangle.width()*2*tan(60), rectangle.top());
            path.lineTo(rectangle.right(), rectangle.top() + rectangle.height()/2);
            path.lineTo(rectangle.right() - rectangle.width()*2*tan(60), rectangle.bottom());
            path.lineTo(rectangle.left() + rectangle.width()*2*tan(60), rectangle.bottom());
            path.lineTo(rectangle.left(), rectangle.top() + rectangle.height()/2);
            path.lineTo(rectangle.left() + rectangle.width()*2*tan(60), rectangle.top());
            painter->fillPath(path, color);
            break;
    }
}

/* Reimplementing ::shape()
 * Collision detection handled by the Graphics View framework using shape-shape intersection.
 * Therefore we have to ensure that the QGraphicsItem::shape() function returns an accurate shape for our Tank.
*/
QPainterPath Tank::shape() const
{
    QRectF rectangle = QRectF(this->get_size()*0.2, this->get_size()*0.2, this->get_size()*0.6, this->get_size()*0.6);
    QPainterPath path;
    // Shape for collision detection
    switch (get_class()) {
        case Tank::TYPE::NORMAL:
            path.addEllipse(this->get_size()*0.2, this->get_size()*0.2, this->get_size()*0.6, this->get_size()*0.6);
            break;
        case Tank::TYPE::GIANT:
            path.addRect(this->get_size()*0.2, this->get_size()*0.2, this->get_size()*0.6, this->get_size()*0.6);
            break;
        case Tank::TYPE::ASSASSIN:
            path.moveTo(rectangle.right(), rectangle.top() + rectangle.height()/2);
            path.lineTo(rectangle.bottomLeft());
            path.lineTo(rectangle.topLeft());
            path.lineTo(rectangle.right(), rectangle.top() + rectangle.height()/2);
            break;
        case Tank::TYPE::SHARPSHOOTER:
            path.addEllipse(this->get_size()*0.25, this->get_size()*0.25, this->get_size()*0.5, this->get_size()*0.5);
            break;
        case Tank::TYPE::ENGINEER:
            path.moveTo(rectangle.left() + rectangle.width()*2*tan(60), rectangle.top());
            path.lineTo(rectangle.right() - rectangle.width()*2*tan(60), rectangle.top());
            path.lineTo(rectangle.right(), rectangle.top() + rectangle.height()/2);
            path.lineTo(rectangle.right() - rectangle.width()*2*tan(60), rectangle.bottom());
            path.lineTo(rectangle.left() + rectangle.width()*2*tan(60), rectangle.bottom());
            path.lineTo(rectangle.left(), rectangle.top() + rectangle.height()/2);
            path.lineTo(rectangle.left() + rectangle.width()*2*tan(60), rectangle.top());
            break;
    }
    return path;
}

//implementing the collision function
void Tank::check_collision() {
    QList<QGraphicsItem *> list = this->collidingItems();
    for(int i = 0; i < list.size();i++) {
        if((typeid(*list[i]) == typeid(Block))){
            Block* the_block= dynamic_cast<Block*>(list[i]);
            this->set_health(this->get_health() - get_collision_damage());
            this->set_xp(this->get_xp() + the_block->get_xp()*0.7); //only gets 70% of the exp
            delete the_block;
        }
        if((typeid(*list[i]) == typeid(Enemy)) && get_subtank() == Tank::SUBTANK::SPINNER && get_skill_status()) {
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
            this->set_max_health(this->get_max_health() * 2);
            this->set_health_regen(this->get_health_regen() * 1.5);
            this->set_vx(this->get_vx() * 1);
            this->set_vy(this->get_vy() * 1);
            this->set_damage(this->get_damage() * 1.2);
            this->set_reload_speed(this->get_reload_speed() - 0.1);
            this->set_bullet_speed(this->get_bullet_speed() * 1);
            break;
        case Tank::TYPE::ASSASSIN:
            this->set_max_health(this->get_max_health() * 1.2);
            this->set_health_regen(this->get_health_regen() * 0.8);
            this->set_vx(this->get_vx() * 1.5);
            this->set_vy(this->get_vy() * 1.5);
            this->set_damage(this->get_damage() * 1);
            this->set_reload_speed(this->get_reload_speed() - 0.2);
            this->set_bullet_speed(this->get_bullet_speed() * 1);
            break;
        case Tank::TYPE::SHARPSHOOTER:
            this->set_max_health(this->get_max_health() * 1);
            this->set_health_regen(this->get_health_regen() * 1);
            this->set_vx(this->get_vx() * 1.2);
            this->set_vy(this->get_vy() * 1.2);
            this->set_damage(this->get_damage() * 2);
            this->set_reload_speed(this->get_reload_speed() + 0.2);
            this->set_bullet_speed(this->get_bullet_speed() * 1.5);
            break;
        case Tank::TYPE::ENGINEER:
            this->set_max_health(this->get_max_health() * 1.5);
            this->set_health_regen(this->get_health_regen() * 1.2);
            this->set_vx(this->get_vx() * 1.2);
            this->set_vy(this->get_vy() * 1.2);
            this->set_damage(this->get_damage() * 1.2);
            this->set_reload_speed(this->get_reload_speed() - 0.1);
            this->set_bullet_speed(this->get_bullet_speed() * 1);
            break;
    }
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

/* The Mutator of Tank Object */
void Tank::set_reload_speed(double reload_speed) { this->reload_speed = reload_speed; }
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
void Tank::increase_sub_tank_evolution_point() {this->sub_tank_evolution_point++;}
void Tank::decrease_sub_tank_evolution_point() {this->sub_tank_evolution_point--;}
void Tank::change_cooldown_status() {this->cooldown_status? this->cooldown_status = false: this->cooldown_status = true;}
void Tank::set_cooldown(int cooldown) {this->cooldown = cooldown;}
void Tank::set_collision_damage(double collision_damage) {this->collision_damage = collision_damage;}
void Tank::change_skill_status() {this->skill_status? this->skill_status = false: this->skill_status = true;}
