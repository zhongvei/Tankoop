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
    ui->show_hud_btn->setFocusPolicy(Qt::NoFocus);
    update_value();
//    ui->groupBox->setStyleSheet("background-color:rgba(41, 70, 255, 0.8);");
    ui->listView->setStyleSheet("background-color:rgba(255, 255, 255);");

    connect(ui->increase_max_health_btn,SIGNAL(clicked()),this,SLOT(increase_max_health_clicked()));
    connect(ui->increase_health_regen_btn,SIGNAL(clicked()),this,SLOT(increase_health_regen_clicked()));
    connect(ui->increase_damage_btn,SIGNAL(clicked()),this,SLOT(increase_damage_clicked()));
    connect(ui->increase_reload_speed_btn,SIGNAL(clicked()),this,SLOT(increase_reload_speed_clicked()));
    connect(ui->increase_movement_speed_btn,SIGNAL(clicked()),this,SLOT(increase_movement_speed_clicked()));
    connect(ui->increase_bullet_speed_btn,SIGNAL(clicked()),this,SLOT(increase_bullet_speed_clicked()));
    connect(ui->show_hud_btn,SIGNAL(clicked()),this,SLOT(show_hud_cicked()));

    connect(ui->ASSASSIN_btn,SIGNAL(clicked()),this,SLOT(ASSASSIN_btn_clicked()));
    connect(ui->sharpshooter_btn,SIGNAL(clicked()),this,SLOT(sharpshooter_btn_clicked()));
    connect(ui->giant_btn,SIGNAL(clicked()),this,SLOT(giant_btn_clicked()));
    connect(ui->engineer_btn,SIGNAL(clicked()),this,SLOT(engineer_btn_clicked()));

}

Hud::~Hud()
{
    delete ui;
}

void Hud::increase_max_health_clicked() {
    if(tank->get_skill_point() >= 1) {
        tank->set_max_health(tank->get_max_health() + 50);
        tank->decrease_skill_point();
    }
}
void Hud::increase_health_regen_clicked() {
    if(tank->get_skill_point() >= 1) {
        tank->set_health_regen(tank->get_health_regen() + 5);
        tank->decrease_skill_point();
    }
}
void Hud::increase_damage_clicked() {
    if(tank->get_skill_point()>=1){
        tank->set_damage(tank->get_damage() + 10);
        tank->decrease_skill_point();
    }
}
void Hud::increase_movement_speed_clicked() {
    if(tank->get_skill_point() >= 1) {
        tank->set_vx(tank->get_vx() + 2);
        tank->set_vy(tank->get_vy() + 2);
        tank->decrease_skill_point();
    }
}
void Hud::increase_reload_speed_clicked() {
    if(tank->get_skill_point() >= 1) {
        tank->set_reload_speed(tank->get_reload_speed() - 0.05);
        tank->decrease_skill_point();
    }
}
void Hud::increase_bullet_speed_clicked() {
    if(tank->get_skill_point() >= 1) {
        tank->set_bullet_speed(tank->get_bullet_speed() + 0.3);
        tank->decrease_skill_point();
    }
}

void Hud::update_value() {
    update_btn_color();
    ui->max_health_value->setText(QString::number(tank->get_max_health()));
    ui->health_regen_value->setText(QString::number(tank->get_health_regen()));
    ui->damage_value->setText(QString::number(tank->get_damage()));
    ui->movement_speed_value->setText(QString::number(tank->get_vx()));
    ui->reload_speed_value->setText(QString::number(tank->get_reload_speed()));
    ui->bullet_speed_value->setText(QString::number(tank->get_bullet_speed()));
    ui->skill_point_value->setText(QString::number(tank->get_skill_point()));
    ui->exp_value->setText(QString::number(tank->get_xp()));
    ui->level_value->setText(QString::number(tank->get_level()));

    if (tank->get_evolution_point() == 1 && tank->get_class() == Tank::TYPE::NORMAL) {
        ui->type_frame->show();
    } else if(tank->get_evolution_point() == 0) {
        ui->type_frame->hide();
    }

    if (tank->get_class() != Tank::TYPE::NORMAL && tank->get_sub_tank_evolution_point() == 1) {
        switch (tank->get_class())
        {
            case Tank::TYPE::NORMAL:
                break;
            case Tank::TYPE::ASSASSIN:
                ui->sub_tank_1->setText("HUNTER");
                ui->sub_tank_2->setText("IMMUNE");
                break;
            case Tank::TYPE::ENGINEER:
                ui->sub_tank_1->setText("SPAWNER");
                ui->sub_tank_2->setText("TRAPPER");
                break;
            case Tank::TYPE::GIANT:
                ui->sub_tank_1->setText("POUNDER");
                ui->sub_tank_2->setText("SPINNER");
                break;
            case Tank::TYPE::SHARPSHOOTER:
                ui->sub_tank_1->setText("DUAL");
                ui->sub_tank_2->setText("SNIPER");
                break;
        }
        ui->sub_tank_frame->show();
    } else {
        ui->sub_tank_frame->hide();
    }

    if(tank->get_skill_status()) {
        ui->skill_status_text->show();
    } else {
        ui->skill_status_text->hide();
    }
}

bool Hud::check_upgrade() {
    if(tank->get_level() > tank->get_skill_point()) {
        return true;
    }
    return false;
}
bool Hud::check_evolution() {
    if(tank->get_evolution_point() == 1) {
        return true;
    }
    return false;
}

void Hud::giant_btn_clicked() {
    if(check_evolution()) {
        tank->change_class(Tank::TYPE::GIANT);
        tank->decrease_evolution_point();
    }
}
void Hud::sharpshooter_btn_clicked() {
    if(check_evolution()) {
        tank->change_class(Tank::TYPE::SHARPSHOOTER);
        tank->decrease_evolution_point();
    }
}
void Hud::engineer_btn_clicked() {
    if(check_evolution()) {
        tank->change_class(Tank::TYPE::ENGINEER);
        tank->decrease_evolution_point();
    }
}
void Hud::ASSASSIN_btn_clicked() {
    if(check_evolution()){
        tank->change_class(Tank::TYPE::ASSASSIN);
        tank->decrease_evolution_point();
    }
}

void Hud::update_btn_color(){
    if(tank->get_skill_point() >= 1) {
        ui->increase_reload_speed_btn->setStyleSheet(UPGRADE_AVAILABLE);
        ui->increase_bullet_speed_btn->setStyleSheet(UPGRADE_AVAILABLE);
        ui->increase_damage_btn->setStyleSheet(UPGRADE_AVAILABLE);
        ui->increase_health_regen_btn->setStyleSheet(UPGRADE_AVAILABLE);
        ui->increase_max_health_btn->setStyleSheet(UPGRADE_AVAILABLE);
        ui->increase_movement_speed_btn->setStyleSheet(UPGRADE_AVAILABLE);
    } else{
        ui->increase_reload_speed_btn->setStyleSheet(UPGRADE_DISABLE);
        ui->increase_bullet_speed_btn->setStyleSheet(UPGRADE_DISABLE);
        ui->increase_damage_btn->setStyleSheet(UPGRADE_DISABLE);
        ui->increase_health_regen_btn->setStyleSheet(UPGRADE_DISABLE);
        ui->increase_max_health_btn->setStyleSheet(UPGRADE_DISABLE);
        ui->increase_movement_speed_btn->setStyleSheet(UPGRADE_DISABLE);
    }
    if(tank->get_evolution_point() >= 1) {
        ui->engineer_btn->setStyleSheet(UPGRADE_AVAILABLE);
        ui->ASSASSIN_btn->setStyleSheet(UPGRADE_AVAILABLE);
        ui->giant_btn->setStyleSheet(UPGRADE_AVAILABLE);
        ui->sharpshooter_btn->setStyleSheet(UPGRADE_AVAILABLE);
    } else {
        ui->engineer_btn->setStyleSheet(UPGRADE_DISABLE);
        ui->ASSASSIN_btn->setStyleSheet(UPGRADE_DISABLE);
        ui->giant_btn->setStyleSheet(UPGRADE_DISABLE);
        ui->sharpshooter_btn->setStyleSheet(UPGRADE_DISABLE);
    }
}

void Hud::show_hud_cicked() {
    if(shown) {
        ui->show_hud_btn->setText(">>>");
        this->move(-220,0);
        shown = false;
    } else {
        ui->show_hud_btn->setText("<<<");
        this->move(0,0);
        shown = true;
    }
}


