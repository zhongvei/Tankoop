#include "GameWindow.h"
#include <QGraphicsRectItem>
#include "GameEntity/Block.h"
#include <cstdlib>
#include <QIcon>
#include <QPointF>
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

    setFixedSize(2000,2000);
    setSceneRect(0,0,2000,2000);

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
//    basic->setPos(0,0);
    basic->setPos(350,250);
    scene->addItem(basic);
    basic->setFlag(QGraphicsItem::ItemIsFocusable);
    basic->setFocus();

    /* Main Loop */
    loop_timer = new QTimer{this};
    //connect(loop_timer, &QTimer::timeout, this, &GameWindow::main_loop);
    connect(loop_timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    //loop_timer->start();
    loop_timer->start(1000/60);

    /* Health Bar Settings */
//    health_bar->setRect(0,0,100,20);
//    health_bar->setPos(100,200);
//    scene->addItem(health_bar);

    //spawn_enemies();

    /* Enemy Spawner */
    enemy_timer = new QTimer{this};
    connect(enemy_timer, &QTimer::timeout, this, &GameWindow::spawn_enemies);
    enemy_timer->start(5000); //adding new enemy every 5 seconds

    /* The HUD */
//    spawn_enemies();

//    health_bar->setRect(0,0,100,20);
//    health_bar->setPos(100,200);
    HealthBar* health_bar = new HealthBar(basic);
//    health_bar->setRect(0,0,100,20);
    scene->addItem(health_bar);
//    QPointF healthpos;
//        healthpos.setX(health_bar->x());
//        healthpos.setY(health_bar->y());
//    qDebug() << basic->mapFromScene(healthpos);

    //health_bar->setPos(healthpos + QPointF(0,70) - basic->mapFromScene(healthpos) );
    // Tank Graphic Test
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

//    for (int i = 0; i < MouseCount; ++i) {
//        TankGraphic *mouse = new TankGraphic;
//        mouse->setPos(::sin((i * 6.28) / MouseCount) * 200,
//                      ::cos((i * 6.28) / MouseCount) * 200);
//        scene->addItem(mouse);
//    }
//    /* Enemy Spawner */
//    enemy_timer = new QTimer{this};
//    connect(enemy_timer, &QTimer::timeout, this, &GameWindow::spawn_enemies);
//    enemy_timer->start(1000); //adding new enemy every 5 seconds
    hud = new Hud(nullptr,basic);
    scene->addWidget(hud);

    show();

}


/*
TODO
Find out how to draw an image on QGraphicsView
Can get inspiration from Spanish dude code
*/
//https://stackoverflow.com/questions/37981512/draw-a-line-with-qpainter-using-qgraphicsview-subclass
//void GameWindow::paintEvent(QPaintEvent *event)
//{
//    qDebug() << "trying to draw";
//    QPainter painter(viewport());
//    painter.setPen(QPen(Qt::black, 12, Qt::DashDotLine, Qt::RoundCap));
//    painter.drawLine(150, 150, 200, 200);

////    painter.setPen(Qt::blue);
////        painter.setFont(QFont("Arial", 30));
////        painter.drawText(100,100, "Qt");

//    QPointF tankpos;
//    tankpos.setX(basic->x());
//    tankpos.setY(basic->y());
//    //QPainter painter(viewport());
////    QRectF target(10.0, 20.0, 80.0, 60.0);
////    //QImage image(R"(D:\Desktop Files\HKUST\2021Fall\COMP 2012H\Project_with_GIT\bruh\resource\gameIcon.jpeg)");

//    QString path ="D:\\Desktop Files\\HKUST\\2021Fall\\COMP 2012H\\Project_with_GIT\\bruh\\resource\\gameIcon.jpeg";
//    QImage image(path);
//    qDebug() <<  path;
//    qDebug() <<  image;
//////    QRectF source(0.0, 0.0, 670.0, 670.0);
////    QRectF source(0.0, 0.0, 70.0, 40.0);
////    //painter.drawImage(target, image, source);
////    // need to be QWidget class to paint
////    painter.drawImage(tankpos, image);
////    painter.fillRect(0,0,200,200,1);
//}

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

//void GameWindow::facing_cursor(Basic* basic) {
//    //calculate degrees
//    QPointF cursor_position = mapToScene(QWidget::mapFromGlobal(QCursor::pos()));
//    double angle_in_radians = std::atan2((cursor_position.y()-(basic->y()+basic->get_size()/2)),(cursor_position.x()-(basic->x()+basic->get_size()/2)));
//    double angle_in_degrees = (angle_in_radians / M_PI) * 180;

//    basic->set_degree(angle_in_degrees);
//    basic->setFocus();
//    //change tank direction
//    QTransform transform;
//    transform.translate(basic->get_size()/2,basic->get_size()/2);
//    transform.rotate(angle_in_degrees);
//    transform.translate(-(basic->get_size()/2),-(basic->get_size()/2));
//    basic->setTransform(transform);

<<<<<<< HEAD
    hud->update_value();
}
=======
//    QPointF tankpos;
//    tankpos.setX(basic->x());
//    tankpos.setY(basic->y());
//    tankpos += QPointF(0,120);


//    //health_bar->setPos(tankpos);

////    QPointF pos = health_bar->mapToItem(basic, 0, 100);
////    health_bar->setPos(pos);
//    hud->update_value();
//}
>>>>>>> b4cce79e58252c5a1fa58bce81969fe95ebd2ccf

void GameWindow::spawn_loop() {
    for(int i = 0; i < 10000; i++) {
        Block* block = new Block(100,100,30,0,0,10,1,0);

        block->setRect(0,0,block->get_size(),block->get_size());
        block->setPos(rand()%9000,rand()%9000);

        scene->addItem(block);
    }
}
