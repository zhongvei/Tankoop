#include "GameWindow.h"
#include "GameEntity/Block.h"
#include "GameEntity/tankgraphic.h"
#include "GameEntity/HealthBar.h"
#include "GameEntity/Enemy.h"
#include "GameEntity/Bullet.h"
#include "Hud.h"

#include <cstdlib>

#include <QIcon>
#include <QPointF>
#include <QList>
#include <QDebug>
#include <QPainter>
#include <QDir>
#include <QtWidgets>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QMessageBox>

GameWindow::GameWindow(QWidget* parent)
{
    this->setWindowTitle("TankOOP");
    this->setWindowIcon(QIcon(":/Resources/icon/tankoop.jpg"));

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

    // Create player Tank (basic)
    basic = new Basic(this);
    basic->setRect(0,0,basic->get_size(),basic->get_size());
    basic->setPos(350,250);
    scene->addItem(basic);
    basic->setFlag(QGraphicsItem::ItemIsFocusable);

    /* Main Loop */
    loop_timer = new QTimer{this};
    connect(loop_timer, &QTimer::timeout, this, &GameWindow::main_loop);
    connect(loop_timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    loop_timer->start(1000/60); // 60 fps

    /* Enemy Spawner */
//    enemy_timer = new QTimer{this};
//    connect(enemy_timer, &QTimer::timeout, this, &GameWindow::spawn_enemies);
//    enemy_timer->start(5000); //adding new enemy every 5 seconds
    spawn_enemies();

    /* Create Health Bar */
    HealthBar* health_bar = new HealthBar(basic, scene);
    scene->addItem(health_bar);


    //spawn the block
    spawn_loop();

    // Tank Graphic Test
//    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    /* The HUD */
    hud = new Hud(this, basic);

    show();
}

void GameWindow::main_loop() {            
    if(!game_over()){
        basic->check_collision();
        hud->update_value();
    } else {
        hud->hide();
        loop_timer->stop();
        QMessageBox* msg_box = new QMessageBox(this);
        msg_box->setText("GAMEOVER!");
        msg_box->show();
    }
}

void GameWindow::spawn_enemies(){
    qDebug() << "NEW ENEMY HAS BEEN ADDED TO THE MAP";
    Enemy *enemy = new Enemy(500,100); // multiple of 50

    enemy->setPos(600,250); //make it random
    enemy->setRect(0,0,enemy->get_size(),enemy->get_size());
    //double scale = enemy->get_size() / enemy->get_range();
    enemy->get_attack_area()->setPos(enemy->x() - enemy->get_size() * (enemy->get_attack_scale()-1)/2, enemy->y() - enemy->get_size() * (enemy->get_attack_scale()-1)/2);
    enemy->get_sight_area()->setPos(enemy->x() - enemy->get_size() * (enemy->get_sight_scale()-1)/2, enemy->y() - enemy->get_size() * (enemy->get_sight_scale()-1)/2);

    HealthBar* health_bar = new HealthBar(enemy, scene);
    scene->addItem(health_bar);

    scene->addItem(enemy);
    scene->addItem(enemy->get_attack_area());
    scene->addItem(enemy->get_sight_area());
}

void GameWindow::spawn_loop() {
    for(int number = 0; number < 300; number++) {
        Block* block = new Block(100,100,30,0,0,10,1,0);
        block->setRect(0,0,block->get_size(),block->get_size());
        block->setPos(rand()%GameWindow::WINDOW_WIDTH,rand()%GameWindow::WINDOW_HEIGHT);
        QTransform transform;
        transform.translate(block->get_size()/2,block->get_size()/2);
        transform.rotate(rand()%360);
        transform.translate(-(block->get_size()/2),-(block->get_size()/2));
        block->setTransform(transform);
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


bool GameWindow::game_over() {
    if(basic->get_health() <= 0) {
        qDebug()<<"gameover";
        return true;
    }
    return false;
}
