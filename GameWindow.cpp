#include "GameWindow.h"

class GameEngine;

GameWindow::GameWindow(int wave, List *list, QWidget* parent, QString nameValue)
{
    /* Setting up the Game Window */
    this->setWindowTitle("TankOOP");
    this->setWindowIcon(QIcon(":/Resources/icon/tankoop.jpg"));
    scene = new QGraphicsScene();
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing); // TODO: check if this makes it more laggy

    /* Set Size of View (Game Window) and Scene (Entire Map) as Maximum to Draw the Background */
    setFixedSize(GameWindow::WINDOW_WIDTH,GameWindow::WINDOW_HEIGHT);
    setSceneRect(0,0,GameWindow::WINDOW_WIDTH,GameWindow::WINDOW_HEIGHT);

    /* Set the Background Color and Draw the Background Grid */
    setStyleSheet("background:rgb(204,204,204)");
    QPen lineColor(QColor(196, 196, 196));
    for(int x = -1; x <= this->width(); x += 28){
        scene->addLine(x,0,x,this->height(),lineColor);
    }
    for(int y = -2; y <= this->height(); y += 28){
        scene->addLine(0,y,this->width(),y,lineColor);
    }

    /* Reduce the Size of View (Game Window) to Appropriate Size */
    setFixedSize(1200,600);

    /* Start the Game Engine */
    GameEngine *game_engine = new GameEngine(this, scene, wave, list, nameValue);
    game_engine->run();

    show();
}

