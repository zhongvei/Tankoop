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
    void entity_spawn();
    int get_enemy_count() const;
    int get_block_count() const;

    void set_enemy_count(int enemy_count);
    void set_block_count(int block_count);
private:
    int enemy_count{};
    int block_count{};

    GameWindow* window;
    QTimer* loop_timer;
    QTimer* enemy_timer;
    QTimer* entity_spawn_timer;
    QTimer* single;
    Tank* player;
    Hud* hud;

};

#endif // GAMEENGINE_H
