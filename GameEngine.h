#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "GameWindow.h"
#include "GameEntity/Tank.h"
#include "Hud.h"
#include "GameEntity/Enemy.h"
#include "List.h"

#include <QObject>
#include <QElapsedTimer>

class GameWindow;
//class Enemy;

class GameEngine: public QObject
{
    Q_OBJECT

public:
    GameEngine(GameWindow* window, QGraphicsScene* scene, int wave = 0, List *list = nullptr);
    void run();
    void main_loop();
    void facing_cursor(Tank* player);
    void spawn_block_loop();
    void spawn_enemies_loop();
    bool game_over();
    void entity_spawn();
    int get_enemy_count() const;
    int get_block_count() const;
    int get_waves() const;

    void set_enemy_count(int enemy_count);
    void set_block_count(int block_count);
    void set_waves(int waves);

private:

    int enemy_count{};
    int block_count{};

    GameWindow* window;
    QTimer* loop_timer;
    QTimer* enemy_timer;
    QTimer* entity_spawn_timer;
    QTimer* single;
    Tank* player = nullptr;
    Hud* hud;

    List *waves_history;
    int waves = 1;
    bool finish_wave = true;
    int max_enemies = 3;
    QGraphicsScene* scene;
    QElapsedTimer elapsed_timer;

};

#endif // GAMEENGINE_H
