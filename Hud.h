#ifndef HUD_H
#define HUD_H

#include "GameEntity/Tank.h"
#include "GameEngine.h"
#include <QWidget>

class GameEngine;

namespace Ui {
class Hud;
}

class Hud : public QWidget
{
    Q_OBJECT

public:
    explicit Hud(QWidget *parent = nullptr,Tank* tank = nullptr,GameEngine* g = nullptr);
    ~Hud();
    void update_value();
    bool check_upgrade();
    bool check_evolution();
public slots:
    void increase_max_health_clicked();
    void increase_health_regen_clicked();
    void increase_damage_clicked();
    void increase_movement_speed_clicked();
    void increase_reload_speed_clicked();
    void increase_bullet_speed_clicked();

    void update_btn_color();
    void show_hud_cicked();

    void giant_btn_clicked();
    void ASSASSIN_btn_clicked();
    void sharpshooter_btn_clicked();
    void engineer_btn_clicked();

    void subtank1_btn_clicked();
    void subtank2_btn_clicked();

private:
    bool shown;
    GameEngine* g;
    Ui::Hud *ui;
    Tank* tank;
};

#endif // HUD_H
