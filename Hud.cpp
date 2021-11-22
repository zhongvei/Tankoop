#include "Hud.h"
#include "ui_Hud.h"
#include <QDebug>

Hud::Hud(QWidget *parent,Tank* tank) :
    QWidget(parent),
    ui(new Ui::Hud),
    tank(tank)
{
    ui->setupUi(this);

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
    tank->set_max_health(tank->get_max_health() + 50);
    tank->setFocus();
}
void Hud::increase_health_regen_clicked() {
    qDebug()<<"hr clicked";
    tank->set_health_regen(tank->get_health_regen() + 5);
    tank->setFocus();
}
void Hud::increase_damage_clicked() {
    qDebug()<<"dmg clicked";
    tank->set_damage(tank->get_damage() + 10);
    tank->setFocus();
}
void Hud::increase_movement_speed_clicked() {
    qDebug()<<"ms clicked";
    tank->set_vx(tank->get_vx() + 7);
    tank->set_vy(tank->get_vy() + 7);
    tank->setFocus();
}
void Hud::increase_attack_speed_clicked() {
    qDebug()<<"as clicked";
    tank->set_attack_speed(tank->get_attack_speed() + 5);
    tank->setFocus();
}
void Hud::increase_bullet_speed_clicked() {
    qDebug()<<"bs clicked";
    tank->set_bullet_speed(tank->get_bullet_speed() + 3);
    tank->setFocus();
}

void Hud::update_value() {
    ui->max_health_value->setText(QString::number(tank->get_max_health()));
    ui->health_regen_value->setText(QString::number(tank->get_health_regen()));
    ui->damage_value->setText(QString::number(tank->get_damage()));
    ui->movement_speed_value->setText(QString::number(tank->get_vx()));
    ui->attack_speed_value->setText(QString::number(tank->get_attack_speed()));
    ui->bullet_speed_value->setText(QString::number(tank->get_bullet_speed()));
    ui->exp_value->setText(QString::number(tank->get_xp()));
    ui->level_value->setText(QString::number(tank->get_level()));
}



