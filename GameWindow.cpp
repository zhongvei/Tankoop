#include "GameWindow.h"
#include "GameEngine.h"

#include <QIcon>
#include <QPointF>
#include <QPainter>
#include <QMediaPlayer>
#include <QUrl>

class GameEngine;

GameWindow::GameWindow(int wave, List *list, QWidget* parent, QString nameValue)
{
    this->setWindowTitle("TankOOP");
    this->setWindowIcon(QIcon(":/Resources/icon/tankoop.jpg"));

    scene = new QGraphicsScene();
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing); // TODO: check if this makes it more laggy

    /* Set size of view (game window) and scene (entire map) as maximum to draw the background */

    setFixedSize(GameWindow::WINDOW_WIDTH,GameWindow::WINDOW_HEIGHT);
    setSceneRect(0,0,GameWindow::WINDOW_WIDTH,GameWindow::WINDOW_HEIGHT);

    /* Set the background color and draw the background grid */

    this->setStyleSheet("background:rgb(204,204,204)");
    QPen lineColor(QColor(196, 196, 196));
    for(int x = -1; x <= this->width(); x += 28){
        scene->addLine(x,0,x,this->height(),lineColor);
    }
    for(int y = -2; y <= this->height(); y += 28){
        scene->addLine(0,y,this->width(),y,lineColor);
    }

    /* reduce size of view (game window) to appropriate size */
    setFixedSize(1200,600);

    /* Play background music */
    QMediaPlayer* music = new QMediaPlayer();
    music->setMedia(QUrl("qrc://Resources/sounds/mainMenu.mp3"));
    music->play();

    /* START THE GAME */
    GameEngine *game_engine = new GameEngine(this, scene, wave, list, nameValue);
    game_engine->run();

    show();
}

//GameWindow::~GameWindow(){
//    delete game_engine;
//    game_engine = nullptr;
//}

