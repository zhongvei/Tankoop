#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "GameWindow.h"
#include "GameEntity/Tank.h"
#include "Hud.h"

#include <QObject>

class GameWindow;

class GameEngine: public QObject
{
    Q_OBJECT
public:
    GameEngine(GameWindow* window);
    void run();
    void main_loop();
    void facing_cursor(Tank* player);
    void spawn_loop();
    void spawn_enemies();
    bool game_over();

private:
    GameWindow* window;
    QTimer* loop_timer;
    QTimer* enemy_timer;
    QTimer* single;
    Tank* player;
    Hud* hud;
};

#endif // GAMEENGINE_H
