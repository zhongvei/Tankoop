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

    /*
     *  @funct: Constructs the Game Engine based on the selected wave from the linked list
     *
     *  @param: window: the game window to enable interaction between the game component and the game interface.
     *          wave: an integer of the selected wave. Default to zero.
     *          list: the linked list being passed to the game to store the game history. Default to nullptr.
     *          nameValue: a QString containing the user's name. Default to empty string.
     *
     *  @return: N/A
     */
    GameEngine(GameWindow* window, int wave = 0, List *list = nullptr, QString nameValue="");

    /*
     *  @funct: Destructs the Game Engine with all of its attributes
     *
     *  @param: N/A
     *  @return: N/A
     */
    ~GameEngine() = default;

    /*
     *  @funct: Setting up the player and its components and creates the Heads Up Display
     *
     *  @param: N/A
     *  @return: N/A
     */
    void run();

    /*
     *  @funct: The main loop of the game. Iterates based on QTimer to update the game, store the data of current wave
     *  to the linked list, and spawn all necessary entities to the game. When game is over, deallocates all the created
     *  entities, calculates the player statistics (performance) and calls the EndGame Window.
     *
     *  @param: N/A
     *  @return: N/A
     */
    void main_loop();

    /*
     *  @funct: Creates blocks for a specific amount of integers and removes doubled / stacked blocks
     *
     *  @param: N/A
     *  @return: N/A
     */
    void spawn_block_loop();

    /*
     *  @funct: Creates enemies and their properties for a specific amount of integers based on the number of waves.
     *
     *  @param: N/A
     *  @return: N/A
     */
    void spawn_enemies_loop();

    /*
     *  @funct: Function to call the enemy spawner and block spawner.
     *
     *  @param: N/A
     *  @return: N/A
     */
    void entity_spawn();

    /*
     *  @funct: Ensures that QVector types cumulativeEnemyNames and cumulativeEnemyScores
     *          has a minimum size of 5 for leaderboard displaying in end screen.
     *
     *  @param: N/A
     *  @return: N/A
     */
    void ensureMin_cumulativeEnemyLists();

    /*
     *  @funct: Appends name and score to (QVector) cumulativeEnemyNames and cumulativeEnemyScores
     *          respectively, adding them to a sorted list.
     *
     *  @param: name: name of the enemy.
     *          score: current score of the enemy.
     *  @return: N/A
     */
    void append_cumulativeEnemyLists(QString name, int score);

    /*
     *  @funct: Function to determine whetehr the game is over or not based on the player's status.
     *
     *  @param: N/A
     *  @return: boolean value
     */
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
    Hud* hud{};
    Tank* player{};
    List *waves_history;

    QElapsedTimer elapsed_timer;
    QString nameValue;
    QMediaPlayer* music;
    QTimer* loop_timer{};
    QTimer* enemy_timer{};
    QTimer* entity_spawn_timer{};
    QTimer* single{};

    int waves = 1;
    int max_enemies = 3;
    int enemy_count{};
    int block_count{};
    bool finish_wave = true;
    bool reset_wave = false;
    bool original = true;

    QVector<QString> cumulativeEnemyNames; // vector that contains all enemies names that spawned and have died during the game
    QVector<int> cumulativeEnemyScores; // vector that contains all enemies scores that spawned and have died during the game


public slots:
    void enemyDied(QString name, int score);

};

#endif // GAMEENGINE_H
