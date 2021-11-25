#ifndef HUD_H
#define HUD_H

#include "GameEntity/Tank.h"
#include <QWidget>

namespace Ui {
class Hud;
}

class Hud : public QWidget
{
    Q_OBJECT

public:
    explicit Hud(QWidget *parent = nullptr,Tank* tank = nullptr);
    ~Hud();
    void update_value();
    bool check_upgrade();
    bool check_evolution();
public slots:
    void increase_max_health_clicked();
    void increase_health_regen_clicked();
    void increase_damage_clicked();
    void increase_movement_speed_clicked();
    void increase_attack_speed_clicked();
    void increase_bullet_speed_clicked();

    void update_btn_color();
    void show_hud_cicked();

    void giant_btn_clicked();
    void assassin_btn_clicked();
    void sharpshooter_btn_clicked();
    void engineer_btn_clicked();


private:
    bool shown;
    Ui::Hud *ui;
    Tank* tank;
};

#endif // HUD_H
