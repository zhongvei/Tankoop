#include "Basic.h"
#include "Bullet.h"
#include "Wall.h"
#include "Turret.h"

#include <QKeyEvent>
#include <QPointF>
#include <QCursor>
#include <QGraphicsView>
#include <QDebug>


//constructor for Basic
Basic::Basic(QGraphicsView* parent, GameEngine* game_engine,
             const double& health, const double& health_regen, const double& max_health,
             const int& size, const double& vx, const double& vy,const double& xp,
             const double& reload_speed,
             const double& bullet_speed,
             const double& damage,
             const int& level,
             const int& skill_point,
             const int& degree):
    Tank(health,health_regen,max_health,size,vx,vy,xp,reload_speed,bullet_speed,damage,level,skill_point,degree),
    UP(false), DOWN(false), RIGHT(false), LEFT(false), parent(parent), game_engine(game_engine)
{
    music->setMedia(QUrl("qrc:/Resources/sounds/shoot.mp3"));
}

//copy constructor for basic
Basic::Basic(const Basic &tank, QGraphicsView *parent, GameEngine* game_engine):Tank(tank), game_engine(game_engine){
    this->parent = parent;
}

GameEntity::CLASS Basic::get_class() const {return GameEntity::CLASS::BASIC;}

//to identified the key pressed by the player
void Basic::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
        case Qt::Key::Key_W:
            UP = true;
            break;
        case Qt::Key::Key_S:
            DOWN = true;
            break;
        case Qt::Key::Key_D:
            RIGHT = true;
            break;
        case Qt::Key::Key_A:
            LEFT = true;
            break;            
        //using the skill of the current sub tank class
        case Qt::Key::Key_Q:
            if (!this->get_cooldown_status()) {
                skill();
                this->change_cooldown_status();
                this->set_cooldown(360); // secs * 60
            }
            break;
    }

    //fires a bullet from the tank where the bullet travels in the direction of the mouse
    if (event->key() == Qt::Key_Space){
        //creates a bullet and check the reload status
        if(!this->get_reload_status()) {
            Bullet * bullet = new Bullet(this,get_damage(),0,10,get_bullet_speed(),get_bullet_speed(), game_engine);
            bullet->set_degree(this->get_degree());
            bullet->setPos(x()+(this->get_size()/2*(1+cos(bullet->get_degree()/57))-bullet->get_size()/2),y()+(this->get_size()/2*(1+sin(bullet->get_degree()/57)))-bullet->get_size()/2);
            
            //some special cases for the sub tank when they are fired in certain state(skill is active)
            if (this->get_subtank() == Tank::SUBTANK::POUNDER && this->get_skill_status() == true) {
                Bullet * bullet2 = new Bullet(this,get_damage(),0,10,get_bullet_speed(),get_bullet_speed(), game_engine);
                bullet2->setPos(x()+(this->get_size()/2*(1+cos((bullet->get_degree()+90)/57))-bullet->get_size()/2),y()+(this->get_size()/2*(1+sin((bullet->get_degree()+90)/57)))-bullet->get_size()/2);
                bullet2->set_degree(this->get_degree()+90);
                scene()->addItem(bullet2);
                Bullet * bullet3 = new Bullet(this,get_damage(),0,10,get_bullet_speed(),get_bullet_speed(), game_engine);
                bullet3->setPos(x()+(this->get_size()/2*(1+cos((bullet->get_degree()+180)/57))-bullet->get_size()/2),y()+(this->get_size()/2*(1+sin((bullet->get_degree()+180)/57)))-bullet->get_size()/2);
                bullet3->set_degree(this->get_degree()+180);
                scene()->addItem(bullet3);
                Bullet * bullet4 = new Bullet(this,get_damage(),0,10,get_bullet_speed(),get_bullet_speed(), game_engine);
                bullet4->setPos(x()+(this->get_size()/2*(1+cos((bullet->get_degree()-90)/57))-bullet->get_size()/2),y()+(this->get_size()/2*(1+sin((bullet->get_degree()-90)/57)))-bullet->get_size()/2);
                bullet4->set_degree(this->get_degree()-90);
                scene()->addItem(bullet4);
            }
            if (this->get_subtank() == Tank::SUBTANK::DUAL && this->get_skill_status() == true) {
                Bullet * bullet2 = new Bullet(this,get_damage(),0,10,get_bullet_speed(),get_bullet_speed(),game_engine);
                bullet2->setPos(x()+(this->get_size()/2*(1+cos((bullet->get_degree()+10)/57))-bullet->get_size()/2),y()+(this->get_size()/2*(1+sin((bullet->get_degree()+10)/57)))-bullet->get_size()/2);
                bullet2->set_degree(this->get_degree()+10);
                scene()->addItem(bullet2);
                Bullet * bullet3 = new Bullet(this,get_damage(),0,10,get_bullet_speed(),get_bullet_speed(),game_engine);
                bullet3->setPos(x()+(this->get_size()/2*(1+cos((bullet->get_degree()-10)/57))-bullet->get_size()/2),y()+(this->get_size()/2*(1+sin((bullet->get_degree()-10)/57)))-bullet->get_size()/2);
                bullet3->set_degree(this->get_degree()-10);
                scene()->addItem(bullet3);
            }

            scene()->addItem(bullet);
            this->change_reload_status();
            this->set_reload_finish(0);

            //setting up the shoot music for basic

            music->setPosition(0);
            music->setVolume(100);
            music->play();
        }

    }

}

//calculate the change of movement if the x axis based on how long the 'W' 'A' 'S' 'D' key is pressed
double Basic::get_changex() {
    bool diagonalMovement = (double) RIGHT - (double) UP ||
         (double) UP - (double) LEFT  ||
         (double) LEFT - (double) DOWN||
         (double) DOWN - (double) RIGHT;

    double result = 0 ;
    if (this->x() > 0 && this->x() < 2000-(this->get_size())) {
        if (diagonalMovement) {
            return (this->get_vx() * ((double)RIGHT - (double)LEFT) / sqrt(2)) / 2;
        }
        else {
            return this->get_vx() * ((double)RIGHT - (double)LEFT) / 2;
        }
    }
    else if (this->x() > 0) {
        result = this->get_vx()*(-(double) LEFT)/2;
    }
    else {
        result = this->get_vx()*((double) RIGHT)/2;
    }
    return result;
}

//calculate the change of movement if the y axis based on how long the 'W' 'A' 'S' 'D' key is pressed
double Basic::get_changey() {
    bool diagonalMovement = (double) RIGHT - (double) UP ||
         (double) UP - (double) LEFT  ||
         (double) LEFT - (double) DOWN||
         (double) DOWN - (double) RIGHT;

    double result = 0 ;
    if (this->y() > 0 && this->y() < 2000-(this->get_size())) {
        if (diagonalMovement) {
            return (this->get_vy() * ((double)DOWN - (double)UP) / sqrt(2)) / 2;
        }
        else {
            return this->get_vy() * ((double)DOWN - (double)UP) / 2;
        }
    }
    else if (this->y() > 0) {
        result = this->get_vy()*(-(double) UP)/2;

    }
    else {
        result = this->get_vy()*((double) DOWN)/2;
    }
    return result;
}

//to identified which key is released by the player
void Basic::keyReleaseEvent(QKeyEvent *event){
    switch(event->key()){
        case Qt::Key::Key_W:
            UP = false;
            break;
        case Qt::Key::Key_S:
            DOWN = false;
            break;
        case Qt::Key::Key_D:
            RIGHT = false;
            break;
        case Qt::Key::Key_A:
            LEFT = false;
            break;
    }

}

//the repeted function that is call such that Basic tank can be moved, fire a bullet and use a skill
void Basic::advance(int step)
{
    if (!step)
        return;
    facing_cursor(this);
    increase_level();
    setFocus();

    if(this->get_reload_status()) {
        set_reload_finish(this->get_reload_finish()+1);
        if(get_reload_finish()== qRound(get_reload_speed()/0.05)) {
            this->change_reload_status();
        }
    }
    if(this->get_cooldown_status()) {
        set_cooldown(this->get_cooldown() - 1);
        if(!this->get_cooldown()) {
            this->change_cooldown_status();
        }

    }
    parent->centerOn(this);

}

void Basic::facing_cursor(Basic* basic) {
    QPointF cursor_position = parent->mapToScene(parent->mapFromGlobal(QCursor::pos()));
    double angle_in_radians = std::atan2((cursor_position.y()-(basic->y()+basic->get_size()/2)),(cursor_position.x()-(basic->x()+basic->get_size()/2)));
    double angle_in_degrees = (angle_in_radians / M_PI) * 180;
    set_degree(angle_in_degrees);

    QTransform transform;
    transform.translate(basic->get_size()/2,basic->get_size()/2);
    transform.rotate(angle_in_degrees);
    transform.translate(-(basic->get_size()/2),-(basic->get_size()/2));
    basic->setTransform(transform);
    basic->setPos(basic->x()+basic->get_changex(),basic->y()+basic->get_changey());
    QPointF pos = basic->pos() + QPointF(16,-40);
    name_item->setPos(pos);
}

void Basic::reset_movement () { UP = false; DOWN = false; RIGHT = false; LEFT = false; }
void Basic::set_parent(QGraphicsView *window) {parent = window;}
void Basic::set_game_engine(GameEngine *game_engine) {this->game_engine = game_engine;}
