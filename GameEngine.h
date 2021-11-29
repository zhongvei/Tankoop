#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "GameWindow.h"
#include "GameEntity/Tank.h"
#include "Hud.h"
#include "GameEntity/Enemy.h"
#include "List.h"

#include <QObject>
#include <QElapsedTimer>
#include <QVector>
#include <QString>

class GameWindow;
class Enemy;
class List;
class Hud;

class GameEngine: public QObject
{
    Q_OBJECT

public:
    GameEngine(GameWindow* window, QGraphicsScene* scene, int wave = 0, List *list = nullptr, QString nameValue="");
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

    void ensureMin_cumulativeEnemyLists();
    void append_cumulativeEnemyLists(QString name, int score);
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
    bool reset_wave = false;
    bool original = true;
    int max_enemies = 3;
    QGraphicsScene* scene;
    QElapsedTimer elapsed_timer;
    QString nameValue;

//    struct enemyStats
//    {
//        QString name = QString("");
//        int score = 0;
//    };

    QVector<QString> cumulativeEnemyNames; // vector that contains all enemies names that spawned and have died during the game
    QVector<int> cumulativeEnemyScores; // vector that contains all enemies scores that spawned and have died during the game

public slots:
    void enemyDied(QString name, int score);
};

#endif // GAMEENGINE_H
