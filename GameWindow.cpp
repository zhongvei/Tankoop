#include "GameWindow.h"
#include <QGraphicsRectItem>
#include "GameEntity/Block.h"
#include <cstdlib>
#include <QIcon>
#include <QPointF>
#include <QList>
#include <QDebug>
#include <QPainter>
#include <QDir>
#include <QApplication>
#include "GameEntity/tankgraphic.h"
#include "GameEntity/HealthBar.h"

#include <QtMath>
#include <QtWidgets>
//static constexpr int MouseCount = 7;

//Basic* health_bar = new Basic();

#include "GameEntity/Enemy.h"
#include <QGraphicsEllipseItem>
#include "Hud.h"

//Basic* health_bar = new Basic();
GameWindow::GameWindow(QWidget* parent)
{
    this->setWindowTitle("TankOOP");
    //this->setWindowIcon(QIcon(R"(C:\Users\zhong\Desktop\Uni\Academic Semester\Fall 2021\COMP 2012H\Tankoop\resource\gameIcon.jpeg)"));
    scene = new QGraphicsScene();

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

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

    //spawn the block
    spawn_loop();

    basic = new Basic(this);
    basic->setRect(0,0,basic->get_size(),basic->get_size());
    basic->setPos(350,250);
    scene->addItem(basic);
    basic->setFlag(QGraphicsItem::ItemIsFocusable);

    /* Main Loop */
    loop_timer = new QTimer{this};
    //connect(loop_timer, &QTimer::timeout, this, &GameWindow::main_loop);
    connect(loop_timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    //loop_timer->start();
    loop_timer->start(1000/60);
    spawn_enemies();
//    /* Enemy Spawner */
//    enemy_timer = new QTimer{this};
//    connect(enemy_timer, &QTimer::timeout, this, &GameWindow::spawn_enemies);
//    enemy_timer->start(5000); //adding new enemy every 5 seconds


//    spawn_enemies();

    HealthBar* health_bar = new HealthBar(basic);
    scene->addItem(health_bar);

    // Tank Graphic Test
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    /* The HUD */
    hud = new Hud(this,basic);

    show();

}

void GameWindow::main_loop() {
    //centerOn(basic);
//    basic->setFocus();
    //health bar as well
    //facing_cursor(basic);

    //basic->setPos(basic->x()+basic->get_changex(),basic->y()+basic->get_changey());

}

void GameWindow::spawn_enemies(){
    qDebug() << "NEW ENEMY HAS BEEN ADDED TO THE MAP";
    Enemy *enemy = new Enemy(300,50); // multiple of 50

    enemy->setPos(rand()%2000,rand()%100); //make it random
    enemy->setRect(0,0,enemy->get_size(),enemy->get_size());
    //double scale = enemy->get_size() / enemy->get_range();
    enemy->get_attack_area()->setPos(enemy->x() - enemy->get_size() * (enemy->get_scale()-1)/2, enemy->y() - enemy->get_size() * (enemy->get_scale()-1)/2);

    scene->addItem(enemy);
    scene->addItem(enemy->get_attack_area());
}

void GameWindow::spawn_loop() {
    for(int number = 0; number < 300; number++) {
        Block* block = new Block(100,100,30,0,0,10,1,0);
        block->setRect(0,0,block->get_size(),block->get_size());
        block->setPos(rand()%GameWindow::WINDOW_WIDTH,rand()%GameWindow::WINDOW_HEIGHT);
        block->setRotation(rand()%360);
        block->setBrush(Qt::red);
        scene->addItem(block);
        QList<QGraphicsItem *> list = block->collidingItems();
        float diagonal = hypot(block->get_size(),block->get_size());
        for(int i =0; i< list.size(); i++) {
            if((typeid(*list[i]) == typeid(Block)) || (typeid(*list[i]) == typeid(Tank)) ) {
                scene->removeItem(list[i]);
                delete list[i];
            }
        }
        if(block->x() < diagonal || block->x() > (GameWindow::WINDOW_WIDTH- diagonal)||
           block->y() < diagonal || block->y() > (GameWindow::WINDOW_HEIGHT- diagonal)) {
            scene->removeItem(block);
            delete block;
        }
    }
}

void GameWindow::mousePressEvent(QMouseEvent *event){
    basic->setFocus();
}
