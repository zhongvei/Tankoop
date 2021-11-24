#include "Hud.h"
#include "ui_Hud.h"
#include <QDebug>


const QString UPGRADE_AVAILABLE= "background-color: rgba(48, 212, 67, 0.8);"
                                 "font: bold 16px;"
                                 "color: white";

const QString UPGRADE_DISABLE = "background-color: rgba(228, 30, 30, 1);"
                                "font: bold 16px;"
                                "color: white";

Hud::Hud(QWidget *parent,Tank* tank) :
    QWidget(parent),
    ui(new Ui::Hud),
    tank(tank)
{
    ui->setupUi(this);
//    this->setStyleSheet("background:rgba(52, 41, 255, 0.8)");
    update_value();

    connect(ui->increase_max_health_btn,SIGNAL(clicked()),this,SLOT(increase_max_health_clicked()));
    connect(ui->increase_health_regen_btn,SIGNAL(clicked()),this,SLOT(increase_health_regen_clicked()));
    connect(ui->increase_damage_btn,SIGNAL(clicked()),this,SLOT(increase_damage_clicked()));
    connect(ui->increase_attack_speed_btn,SIGNAL(clicked()),this,SLOT(increase_attack_speed_clicked()));
    connect(ui->increase_movement_speed_btn,SIGNAL(clicked()),this,SLOT(increase_movement_speed_clicked()));
    connect(ui->increase_bullet_speed_btn,SIGNAL(clicked()),this,SLOT(increase_bullet_speed_clicked()));


}

Hud::~Hud()
{
    delete ui;
}

void Hud::increase_max_health_clicked() {
    qDebug()<<"mh clicked";
    if(tank->get_skill_point() >= 1) {
        tank->set_max_health(tank->get_max_health() + 50);
        tank->decrease_skill_point();
    }
    tank->setFocus();
}
void Hud::increase_health_regen_clicked() {
    qDebug()<<"hr clicked";
    if(tank->get_skill_point() >= 1) {
        tank->set_health_regen(tank->get_health_regen() + 5);
        tank->decrease_skill_point();
    }
    tank->setFocus();
}
void Hud::increase_damage_clicked() {
    qDebug()<<"dmg clicked";
    if(tank->get_skill_point()>=1){
        tank->set_damage(tank->get_damage() + 10);
        tank->decrease_skill_point();
    }
    tank->setFocus();
}
void Hud::increase_movement_speed_clicked() {
    qDebug()<<"ms clicked";
    if(tank->get_skill_point() >= 1) {
        tank->set_vx(tank->get_vx() + 7);
        tank->set_vy(tank->get_vy() + 7);
        tank->decrease_skill_point();
    }
    tank->setFocus();
}
void Hud::increase_attack_speed_clicked() {
    qDebug()<<"as clicked";
    if(tank->get_skill_point() >= 1) {
        tank->set_attack_speed(tank->get_attack_speed() + 5);
        tank->decrease_skill_point();
    }
    tank->setFocus();
}
void Hud::increase_bullet_speed_clicked() {
    qDebug()<<"bs clicked";
    if(tank->get_skill_point() >= 1) {
        tank->set_bullet_speed(tank->get_bullet_speed() + 3);
        tank->decrease_skill_point();
    }
    tank->setFocus();
}

void Hud::update_value() {
    update_btn_color();
    ui->max_health_value->setText(QString::number(tank->get_max_health()));
    ui->health_regen_value->setText(QString::number(tank->get_health_regen()));
    ui->damage_value->setText(QString::number(tank->get_damage()));
    ui->movement_speed_value->setText(QString::number(tank->get_vx()));
    ui->attack_speed_value->setText(QString::number(tank->get_attack_speed()));
    ui->bullet_speed_value->setText(QString::number(tank->get_bullet_speed()));
    ui->skill_point_value->setText(QString::number(tank->get_skill_point()));

    increase_level();
    ui->exp_value->setText(QString::number(tank->get_xp()));
    ui->level_value->setText(QString::number(tank->get_level()));
}

void Hud::increase_level() {
    if((tank->get_level()*100 - tank->get_xp())/100 > 1) {
       tank->set_level(tank->get_level() + 1);
       tank->increase_skill_point();
       qDebug()<<"INCREASED LEVEL BY 1";
    }
}

bool Hud::check_upgrade() {
    if(tank->get_level() > tank->get_skill_point()) {
        return true;
    }
    return false;
}

void Hud::update_btn_color(){
    if(tank->get_skill_point() >= 1) {
        ui->increase_attack_speed_btn->setStyleSheet(UPGRADE_AVAILABLE);
        ui->increase_bullet_speed_btn->setStyleSheet(UPGRADE_AVAILABLE);
        ui->increase_damage_btn->setStyleSheet(UPGRADE_AVAILABLE);
        ui->increase_health_regen_btn->setStyleSheet(UPGRADE_AVAILABLE);
        ui->increase_max_health_btn->setStyleSheet(UPGRADE_AVAILABLE);
        ui->increase_movement_speed_btn->setStyleSheet(UPGRADE_AVAILABLE);
    } else{
        ui->increase_attack_speed_btn->setStyleSheet(UPGRADE_DISABLE);
        ui->increase_bullet_speed_btn->setStyleSheet(UPGRADE_DISABLE);
        ui->increase_damage_btn->setStyleSheet(UPGRADE_DISABLE);
        ui->increase_health_regen_btn->setStyleSheet(UPGRADE_DISABLE);
        ui->increase_max_health_btn->setStyleSheet(UPGRADE_DISABLE);
        ui->increase_movement_speed_btn->setStyleSheet(UPGRADE_DISABLE);
    }
}


