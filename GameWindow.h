#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "GameEngine.h"
#include "List.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QString>
#include <QIcon>
#include <QPointF>
#include <QPainter>

class List;
class GameEngine;

class GameWindow : public QGraphicsView
{
    Q_OBJECT

public:

    /*
     *  @funct: Constructs the Game Window with all of its attributes. Setting up the screen and background of the games and
     *          and creates the Game Engine class.
     *
     *  @param: wave: the integer of the selected wave. Default to zero.
     *          list: the linked list being passed to the game to store the game history. Default to nullptr.
     *          parent: to access the widget in the game window interface. Default to nullptr.
     *          nameValue: a QString containing the user's name.
     *
     *  @return: N/A
     */
    explicit GameWindow(int wave = 0, List *list = nullptr, QWidget* parent = 0, QString nameValue="");

    /*
     *  @funct: Destructs the Game Window with all of its attributes. Deallocating all memories.
     *
     *  @param: N/A
     *  @return: N/A
     */
    ~GameWindow();

    /* Global Variable */
    const static int WINDOW_WIDTH = 2000;
    const static int WINDOW_HEIGHT = 2000;

    QGraphicsScene *scene;
    GameEngine *game_engine;

};

#endif // GAMEWINDOW_H
