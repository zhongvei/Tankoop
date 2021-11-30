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
    /*
    *  @funct:  the constructor for the Hud
    *  @param:  parent: the window that the Hud is being created at, tank: the tank which the player is currently controlling
    *  @param:  g: the game engine that creates the hud
    *  @return: N/A
    */
    explicit Hud(QWidget *parent = nullptr,Tank* tank = nullptr,GameEngine* g = nullptr);

    /*
    *  @funct:  the destructor for the Hud
    *  @param:  N/A
    *  @return: N/A
    */
    ~Hud();

    /*
    *  @funct:  the function to update the values and text in the HUD on the GameWindow
    *  @param:  N/A
    *  @return: N/A
    */
    void update_value();

    /*
    *  @funct:  check whetherevolution is available
    *  @param:  N/A
    *  @return: bool: true if evolutionis available, false otherwise
    */
    bool check_evolution();

public slots:
    /*
    *  @funct:  the event where the increase_max_health_button is clicked on the HUD
    *  @param:  N/A
    *  @return: N/A
    */
    void increase_max_health_clicked();

    /*
    *  @funct:  the event where the increase_health_regen_button is clicked on the HUD
    *  @param:  N/A
    *  @return: N/A
    */
    void increase_health_regen_clicked();

    /*
    *  @funct:  the event where the increase_damage_button is clicked on the HUD
    *  @param:  N/A
    *  @return: N/A
    */
    void increase_damage_clicked();

    /*
    *  @funct:  the event where the increase_movement_speed_button is clicked on the HUD
    *  @param:  N/A
    *  @return: N/A
    */
    void increase_movement_speed_clicked();

    /*
    *  @funct:  the event where the increase_reload_speed_button is clicked on the HUD
    *  @param:  N/A
    *  @return: N/A
    */
    void increase_reload_speed_clicked();

    /*
    *  @funct:  the event where the increase_bullet_speed_button is clicked on the HUD
    *  @param:  N/A
    *  @return: N/A
    */
    void increase_bullet_speed_clicked();

    /*
    *  @funct:  checks whether an upgrade is available and updates the HUD button accordingly
    *  @param:  N/A
    *  @return: N/A
    */
    void update_btn_color();

    /*
    *  @funct:  the event where the show_hud_button is clicked on the HUD
    *  @param:  N/A
    *  @return: N/A
    */
    void show_hud_cicked();

    /*
    *  @funct:  the event where the giant_button is clicked on the HUD
    *  @param:  N/A
    *  @return: N/A
    */
    void giant_btn_clicked();

    /*
    *  @funct:  the event where the ASSASSIN_button is clicked on the HUD
    *  @param:  N/A
    *  @return: N/A
    */
    void ASSASSIN_btn_clicked();

    /*
    *  @funct:  the event where the sharpshooter_button is clicked on the HUD
    *  @param:  N/A
    *  @return: N/A
    */
    void sharpshooter_btn_clicked();

    /*
    *  @funct:  the event where the engineer_button is clicked on the HUD
    *  @param:  N/A
    *  @return: N/A
    */
    void engineer_btn_clicked();

    /*
    *  @funct:  the event where the subtank1_button is clicked on the HUD
    *  @param:  N/A
    *  @return: N/A
    */
    void subtank1_btn_clicked();

    /*
    *  @funct:  the event where the subtank2_button is clicked on the HUD
    *  @param:  N/A
    *  @return: N/A
    */
    void subtank2_btn_clicked();

private:
    bool shown;
    GameEngine* g;
    Ui::Hud *ui;
    Tank* tank;
};

#endif // HUD_H
