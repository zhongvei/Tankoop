 #ifndef BASIC_H
#define BASIC_H

#include "Tank.h"
#include "../GameEngine.h"

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsRotation>
#include <QTransform>
#include <QMediaPlayer>

class GameEngine;

class Basic: public Tank, public QGraphicsRotation, public QTransform
{
public:
    /*
    *  @funct:  the constructor for the Basic, default values are set since the player are given the same stats every new game
    *  @funct:  every player starts a new game as a Basic object 
    *
    *  @param:  parent: the view that Basic is created on, game_engine: the gameengine that creates Basic  
    *  @param:  health_regen: initial health regen for Basic, max_health: initial max_health for Basic,
    *  @param:  health: initial health for Basic, health_regen: initial health regen for Basic, max_health: initial max_health for Basic,
    *  @param:  size: initial size for Basic, vx: initial movement speed in the x axis for Basic, vy: initial movement speed in the y axis for Basic,
    *  @param:  xp: initial experience point for Basic, level: initial level for Basic, skill_point: the initial skill_point for Basic
    *  @param:  degree: the initial angle which the Bullet will be fire from the Basic object
    *  @return: N/A     
    */
    Basic(QGraphicsView* parent=nullptr, GameEngine* game_engine=nullptr,
          const double& health = 300, const double& health_regen = 1, const double& max_health = 300,
          const int& size = 100, const double& vx = 10, const double& vy = 10,const double& xp = 0,
          const double& reload_speed = 0.8,
          const double& bullet_speed = 0.6,
          const double& damage = 50,
          const int& level = 1,
          const int& skill_point = 0,
          const int& degree = 0
    );

    /*
    *  @funct:  a copy constructor for the Basic
    *
    *  @param:  basic: the Basic object that is being copied from, parent: the view that the Baisc object is on, game_engine: the gameengine that creates Basic
    *  @return: N/A
    */
    Basic(const Basic &basic,  QGraphicsView *parent = nullptr,GameEngine* game_engine=nullptr);

    /*
    *  @funct:  an override function from QGraphicsRectItem to identify which key is pressed by the player
    *
    *  @param:  event: the key that is pressed on the keyboard will be passed as this parameter
    *  @return: N/A     
    */
    void keyPressEvent(QKeyEvent * event) override;

    /*
    *  @funct:  an override function from QGraphicsRectItem to identify which key is released by the player
    *
    *  @param:  event: the key that is released on the keyboard will be passed as this parameter
    *  @return: N/A     
    */
    void keyReleaseEvent(QKeyEvent *event) override;


    /*
    *  @funct:  reset all the key pressed by the user by setting UP, DOWN, RIGHT, LEFT to false
    *
    *  @param:  N/A
    *  @return: N/A     
    */
    void reset_movement();

    /*
    *  @funct:  changing the direction which the bullet is fire by the player based on the angle between the mouse and Basic
    *
    *  @param:  basic: the Basic object that is controlled by the user
    *  @return: N/A     
    */
    void facing_cursor(Basic* basic);

    /*
    *  @funct:  get the change of movement of the player in the x axis
    *
    *  @param:  N/A
    *  @return: double: the change of movement in the x axis      
    */
    double get_changex();

    /*
    *  @funct:  get the change of movement of the player in the y axis
    *
    *  @param:  N/A
    *  @return: double: the change of movement in the y axis      
    */
    double get_changey();

    /*
    *  @funct:  set the parent of Basic, which is the GameWindow that Basic is created at  
    *
    *  @param:  window: the parent of Basic, which is the GameWindow that Basic is created at
    *  @return: N/A      
    */
    void set_parent(QGraphicsView* window);


    /*
    *  @funct:  get the GameEntity class, which is GameEntity::CLASS::TANK in this case
    *  @param:  N/A
    *  @return: GameEntitiy::CLASS: the GameEntity class, which is GameEntity::CLASS::TANK in this case
    */
    GameEntity::CLASS get_class() const override;

    GameEngine*  game_engine;

private:
    double changex = 0;
    double changey = 0;

    int skill_cooldown;
    bool cooldown_status;

    bool UP, DOWN, RIGHT, LEFT;


    QGraphicsView* parent{};

protected:
    /*
    *  @funct:  an override function from QGraphicsRectItem such that this function is being repetedly called by the GameEngine
    *
    *  @param:  step: the phase of the function, step = 0 would not run the function body
    *  @return: N/A     
    */
    void advance(int step) override;

};

#endif // BASIC_H
