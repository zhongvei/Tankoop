#ifndef HUD_H
#define HUD_H

#include <QWidget>
#include "GameEntity/Tank.h"

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
public slots:
    void increase_max_health_clicked();
    void increase_health_regen_clicked();
    void increase_damage_clicked();
    void increase_movement_speed_clicked();
    void increase_attack_speed_clicked();
    void increase_bullet_speed_clicked();

    void increase_level();
    void update_btn_color();
    bool check_upgrade();

private:
    Ui::Hud *ui;
    Tank* tank;
};

#endif // HUD_H
