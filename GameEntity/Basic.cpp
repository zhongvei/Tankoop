#include "Basic.h"
#include "Bullet.h"
#include "Wall.h"

#include <QKeyEvent>
#include <QPointF>
#include <QCursor>
#include <QGraphicsView>
#include <QDebug>

Basic::Basic(QGraphicsView* parent): Tank(300,1,300,100,10,10,0,0.8,0.6,50,1,0,0),
    parent(parent), UP(false), DOWN(false), RIGHT(false), LEFT(false) {
}

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
        case Qt::Key::Key_Q:
            if (!this->get_cooldown_status()) {
                qDebug()<<"SKILL PRESSED";
                skill();
                this->change_cooldown_status();
                this->set_cooldown(360); // secs * 60

                if(this->get_subtank() == Tank::SUBTANK::TRAPPER){
                    Wall* wall = new Wall(this->get_degree());
                    wall->setPos(x()+((this->get_size()/2)*(1+cos(this->get_degree()/57))-10/2),
                                 y()+((this->get_size()/2)*(1+sin(this->get_degree()/57)))-wall->get_size()/2);
                    QTransform transform;
                    transform.translate(10/2,this->get_size()/2);
                    transform.rotate(get_degree());
                    transform.translate(-(10/2),-(this->get_size()/2));
                    wall->setTransform(transform);
                    scene()->addItem(wall);
                }
            }
            break;
    }

    if (event->key() == Qt::Key_Space){
        /* Create a bullet */
        if(!this->get_reload_status()) {
            Bullet * bullet = new Bullet(this,get_damage(),0,10,get_bullet_speed(),get_bullet_speed());
            bullet->set_degree(this->get_degree());
            bullet->setPos(x()+(this->get_size()/2*(1+cos(bullet->get_degree()/57))-bullet->get_size()/2),y()+(this->get_size()/2*(1+sin(bullet->get_degree()/57)))-bullet->get_size()/2);

            if (this->get_subtank() == Tank::SUBTANK::POUNDER && this->get_skill_status() == true) {
                Bullet * bullet2 = new Bullet(this,get_damage(),0,10,get_bullet_speed(),get_bullet_speed());
                bullet2->setPos(x()+(this->get_size()/2*(1+cos((bullet->get_degree()+90)/57))-bullet->get_size()/2),y()+(this->get_size()/2*(1+sin((bullet->get_degree()+90)/57)))-bullet->get_size()/2);
                bullet2->set_degree(this->get_degree()+90);
                scene()->addItem(bullet2);
                Bullet * bullet3 = new Bullet(this,get_damage(),0,10,get_bullet_speed(),get_bullet_speed());
                bullet3->setPos(x()+(this->get_size()/2*(1+cos((bullet->get_degree()+180)/57))-bullet->get_size()/2),y()+(this->get_size()/2*(1+sin((bullet->get_degree()+180)/57)))-bullet->get_size()/2);
                bullet3->set_degree(this->get_degree()+180);
                scene()->addItem(bullet3);
                Bullet * bullet4 = new Bullet(this,get_damage(),0,10,get_bullet_speed(),get_bullet_speed());
                bullet4->setPos(x()+(this->get_size()/2*(1+cos((bullet->get_degree()-90)/57))-bullet->get_size()/2),y()+(this->get_size()/2*(1+sin((bullet->get_degree()-90)/57)))-bullet->get_size()/2);
                bullet4->set_degree(this->get_degree()-90);
                scene()->addItem(bullet4);
            }
            if (this->get_subtank() == Tank::SUBTANK::DUAL && this->get_skill_status() == true) {
                Bullet * bullet2 = new Bullet(this,get_damage(),0,10,get_bullet_speed(),get_bullet_speed());
                bullet2->setPos(x()+(this->get_size()/2*(1+cos((bullet->get_degree()+10)/57))-bullet->get_size()/2),y()+(this->get_size()/2*(1+sin((bullet->get_degree()+10)/57)))-bullet->get_size()/2);
                bullet2->set_degree(this->get_degree()+10);
                scene()->addItem(bullet2);
                Bullet * bullet3 = new Bullet(this,get_damage(),0,10,get_bullet_speed(),get_bullet_speed());
                bullet3->setPos(x()+(this->get_size()/2*(1+cos((bullet->get_degree()-10)/57))-bullet->get_size()/2),y()+(this->get_size()/2*(1+sin((bullet->get_degree()-10)/57)))-bullet->get_size()/2);
                bullet3->set_degree(this->get_degree()-10);
                scene()->addItem(bullet3);
            }

            scene()->addItem(bullet);
            this->change_reload_status();
            this->set_reload_finish(0);
        }

    }

}


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

    // dont delete
//    QPainter painter(QPaintDevice);
//    //painter.setPen(QPen(Qt::black), 1);
//    painter.drawRect(this->x(), this->y(), 200,200);

    // IF THIS BASIC IS THE USER: THEN CENTER ON. ELSE, DONT CENTER ON
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
}
