#include "GameWindow.h"
#include <QGraphicsRectItem>
#include "GameEntity/Block.h"
#include <cstdlib>
#include <QIcon>
#include <QPointF>
#include <QList>
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

    //create and set up the tank
    basic = new Basic();
    basic->setRect(0,0,basic->get_size(),basic->get_size());
    basic->setPos(350,250);
    scene->addItem(basic);
    basic->setFlag(QGraphicsItem::ItemIsFocusable);

    /* Main Loop */
    loop_timer = new QTimer{this};
    connect(loop_timer, &QTimer::timeout, this, &GameWindow::main_loop);
    loop_timer->start();

    /* Health Bar Settings */
//    health_bar->setRect(0,0,100,20);
//    health_bar->setPos(100,200);
//    scene->addItem(health_bar);

//    spawn_enemies();

//    /* Enemy Spawner */
//    enemy_timer = new QTimer{this};
//    connect(enemy_timer, &QTimer::timeout, this, &GameWindow::spawn_enemies);
//    enemy_timer->start(1000); //adding new enemy every 5 seconds

    //make a new hud
    hud = new Hud(this,basic);

    show();

}

void GameWindow::main_loop() {
    centerOn(basic);
    //health bar as well
    facing_cursor(basic);

    basic->setPos(basic->x()+basic->get_changex(),basic->y()+basic->get_changey());
//    hud->check_upgrade();

}

void GameWindow::spawn_enemies(){
    qDebug() << "NEW ENEMY HAS BEEN ADDED TO THE MAP";
    Enemy *enemy = new Enemy(300,50); // multiple of 50

    enemy->setPos(600,250); //make it random
    enemy->setRect(0,0,enemy->get_size(),enemy->get_size());
    //double scale = enemy->get_size() / enemy->get_range();
    enemy->get_attack_area()->setPos(enemy->x() - enemy->get_size() * (enemy->get_scale()-1)/2, enemy->y() - enemy->get_size() * (enemy->get_scale()-1)/2);

    scene->addItem(enemy);
    scene->addItem(enemy->get_attack_area());
}

void GameWindow::facing_cursor(Basic* basic) {
    //calculate degrees
    QPointF cursor_position = mapToScene(QWidget::mapFromGlobal(QCursor::pos()));
    double angle_in_radians = std::atan2((cursor_position.y()-(basic->y()+basic->get_size()/2)),(cursor_position.x()-(basic->x()+basic->get_size()/2)));
    double angle_in_degrees = (angle_in_radians / M_PI) * 180;

    basic->set_degree(angle_in_degrees);
    //change tank direction
    QTransform transform;
    transform.translate(basic->get_size()/2,basic->get_size()/2);
    transform.rotate(angle_in_degrees);
    transform.translate(-(basic->get_size()/2),-(basic->get_size()/2));
    basic->setTransform(transform);

    QPointF tankpos;
    tankpos.setX(basic->x());
    tankpos.setY(basic->y());
    tankpos += QPointF(0,120);


    //health_bar->setPos(tankpos);

//    QPointF pos = health_bar->mapToItem(basic, 0, 100);
//    health_bar->setPos(pos);
        hud->update_value();
//    QPoint pos = QPoint(100,100);

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

void GameWindow::mousePressEvent(QMouseEvent *event) {
    basic->setFocus();
}
