#include "Hud.h"
#include "ui_Hud.h"
#include <QDebug>


const QString UPGRADE_AVAILABLE= "background-color: rgba(48, 212, 67, 0.8);"
                                 "font: bold 10px;"
                                 "color: white";

const QString UPGRADE_DISABLE = "background-color: rgba(228, 30, 30, 1);"
                                "font: bold 10px;"
                                "color: white";

Hud::Hud(QWidget *parent,Tank* tank,GameEngine* g) :
    QWidget(parent),
    g(g),
    ui(new Ui::Hud),
    tank(tank)
{
    ui->setupUi(this);
    ui->show_hud_btn->setFocusPolicy(Qt::NoFocus);
    ui->engineer_btn->setStyleSheet(UPGRADE_AVAILABLE);
    ui->ASSASSIN_btn->setStyleSheet(UPGRADE_AVAILABLE);
    ui->giant_btn->setStyleSheet(UPGRADE_AVAILABLE);
    ui->sharpshooter_btn->setStyleSheet(UPGRADE_AVAILABLE);
    ui->sub_tank_1->setStyleSheet(UPGRADE_AVAILABLE);
    ui->sub_tank_2->setStyleSheet(UPGRADE_AVAILABLE);

    ui->stackedWidget->setCurrentIndex(2);

    ui->wave_frame->setStyleSheet("background-color: transparent");
    ui->skill_cooldown_frame->setStyleSheet("background-color: transparent");
    ui->skill_status_frame->setStyleSheet("background-color: transparent");

    update_value();

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

    connect(ui->sub_tank_1,SIGNAL(clicked()),this,SLOT(subtank1_btn_clicked()));
    connect(ui->sub_tank_2,SIGNAL(clicked()),this,SLOT(subtank2_btn_clicked()));

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
        tank->set_health_regen(tank->get_health_regen() + 1);
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
    ui->wave_value->setText(QString::number(g->get_waves()));

    if (tank->get_evolution_point() == 1 && tank->get_type() == Tank::TYPE::NORMAL) {
        ui->stackedWidget->setCurrentIndex(0);
    } else if(tank->get_type() != Tank::TYPE::NORMAL && tank->get_sub_tank_evolution_point() == 1) {
        ui->stackedWidget->setCurrentIndex(1);
    } else {
        ui->stackedWidget->setCurrentIndex(2);
    }

    if (tank->get_type() != Tank::TYPE::NORMAL && tank->get_sub_tank_evolution_point() == 1) {
        switch (tank->get_type())
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
    }

    if(tank->get_skill_status() &&
       tank->get_subtank() != Tank::SUBTANK::DEFAULT &&
       tank->get_type() != Tank::TYPE::ENGINEER) {
        ui->skill_status_frame->show();
    } else {
        ui->skill_status_frame->hide();
    }
    if(tank->get_subtank() != Tank::SUBTANK::DEFAULT) {
        ui->cooldown_text->setText(QString::number(tank->get_cooldown() / 60));
        ui->skill_cooldown_frame->show();
    } else {
        ui->skill_cooldown_frame->hide();
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
        tank->change_type(Tank::TYPE::GIANT);
        tank->decrease_evolution_point();
    }
}
void Hud::sharpshooter_btn_clicked() {
    if(check_evolution()) {
        tank->change_type(Tank::TYPE::SHARPSHOOTER);
        tank->decrease_evolution_point();
    }
}
void Hud::engineer_btn_clicked() {
    if(check_evolution()) {
        tank->change_type(Tank::TYPE::ENGINEER);
        tank->decrease_evolution_point();
    }
}
void Hud::ASSASSIN_btn_clicked() {
    if(check_evolution()){
        tank->change_type(Tank::TYPE::ASSASSIN);
        tank->decrease_evolution_point();
    }
}

void Hud::subtank1_btn_clicked() {
    switch(tank->get_type()) {
        case Tank::TYPE::GIANT:
            tank->change_subtank(Tank::SUBTANK::POUNDER);
            tank->decrease_sub_tank_evolution_point();
            break;
        case Tank::TYPE::ASSASSIN:
            tank->change_subtank(Tank::SUBTANK::HUNTER);
            tank->decrease_sub_tank_evolution_point();
            break;
        case Tank::TYPE::SHARPSHOOTER:
            tank->change_subtank(Tank::SUBTANK::DUAL);
            tank->decrease_sub_tank_evolution_point();
            break;
        case Tank::TYPE::ENGINEER:
            tank->change_subtank(Tank::SUBTANK::SPAWNER);
            tank->decrease_sub_tank_evolution_point();
            break;
        default:
            break;
    }
}
void Hud::subtank2_btn_clicked() {
    switch(tank->get_type()) {
        case Tank::TYPE::GIANT:
            tank->change_subtank(Tank::SUBTANK::SPINNER);
            tank->decrease_sub_tank_evolution_point();
            break;
        case Tank::TYPE::ASSASSIN:
            tank->change_subtank(Tank::SUBTANK::IMMUNE);
            tank->decrease_sub_tank_evolution_point();
            break;
        case Tank::TYPE::SHARPSHOOTER:
            tank->change_subtank(Tank::SUBTANK::SNIPER);
            tank->decrease_sub_tank_evolution_point();
            break;
        case Tank::TYPE::ENGINEER:
            tank->change_subtank(Tank::SUBTANK::TRAPPER);
            tank->decrease_sub_tank_evolution_point();
            break;
        default:
            break;
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
