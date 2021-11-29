#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "GameWindow.h"
#include "EndGameWindow.h"
#include "Hud.h"
#include "List.h"
#include "GameEntity/Tank.h"
#include "GameEntity/Enemy.h"
#include "GameEntity/Basic.h"
#include "GameEntity/Bullet.h"
#include "GameEntity/HealthBar.h"

#include <QObject>
#include <QElapsedTimer>
#include <QVector>
#include <QString>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QRandomGenerator>
#include <QMessageBox>
#include <QDebug>
#include <QColor>

class GameWindow;
class Enemy;
class List;
class Hud;

class GameEngine: public QObject
{
    Q_OBJECT

public:
    GameEngine(GameWindow* window, QGraphicsScene* scene, int wave = 0, List *list = nullptr, QString nameValue="");
    ~GameEngine() = default;

    void run();
    void main_loop();
    void facing_cursor(Tank* player);
    void spawn_block_loop();
    void spawn_enemies_loop();
    void entity_spawn();
    void ensureMin_cumulativeEnemyLists();
    void append_cumulativeEnemyLists(QString name, int score);
    bool game_over();


    /* Accessor */
    int get_enemy_count() const;
    int get_block_count() const;
    int get_waves() const;

    /* Mutator */
    void set_enemy_count(int enemy_count);
    void set_block_count(int block_count);
    void set_waves(int waves);

private:

    GameWindow* window{};
    QTimer* loop_timer{};
    QTimer* enemy_timer{};
    QTimer* entity_spawn_timer{};
    QTimer* single{};
    Hud* hud{};
    Tank* player{};

    List *waves_history;

    QGraphicsScene* scene;
    QElapsedTimer elapsed_timer;
    QString nameValue;

    int waves = 1;
    int max_enemies = 3;
    int enemy_count{};
    int block_count{};
    bool finish_wave = true;
    bool reset_wave = false;
    bool original = true;

    QVector<QString> cumulativeEnemyNames; // vector that contains all enemies names that spawned and have died during the game
    QVector<int> cumulativeEnemyScores; // vector that contains all enemies scores that spawned and have died during the game

    QMediaPlayer* music;


public slots:
    void enemyDied(QString name, int score);

};

#endif // GAMEENGINE_H
