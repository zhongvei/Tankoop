#include "GameWindow.h"
#include <QGraphicsRectItem>
#include "GameEntity/myRect.h"
#include "GameEntity/View.h"
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

GameWindow::GameWindow(QWidget* parent)
{
    this->setWindowTitle("TankOOP");
    //this->setWindowIcon(QIcon(R"(C:\Users\zhong\Desktop\Uni\Academic Semester\Fall 2021\COMP 2012H\Tankoop\resource\gameIcon.jpeg)"));
    scene = new QGraphicsScene();

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // set size of view (game window) and scene (entire map) as maximum to draw background
    setFixedSize(2000,2000);
    setSceneRect(0,0,2000,2000);

    // set background color and draw background grid
    this->setStyleSheet("background:rgb(204,204,204)");
    QPen lineColor(QColor(196, 196, 196));
    for(int x = -1; x <= this->width(); x += 28){
        scene->addLine(x,0,x,this->height(),lineColor);
    }
    for(int y = -2; y <= this->height(); y += 28){
        scene->addLine(0,y,this->width(),y,lineColor);
    }
    // reduce size of view (game window) to appropriate size
    setFixedSize(1200,600);

    spawn_loop();
//    MyRect* enemy = new MyRect();
//    enemy->setRect(0,0,100,100);
//    enemy->setPos(100,100);
//    scene->addItem(enemy);

    basic = new Basic(this);
    basic->setRect(0,0,basic->get_size(),basic->get_size());
//    basic->setPos(0,0);
    basic->setPos(350,250);
    scene->addItem(basic);

        QPoint healthpos;
            healthpos.setX(basic->x());
            healthpos.setY(basic->y());
    QPointF basic_viewport_coords = mapToScene(healthpos);

    //scene->addRect(basic_viewport_coords.x()-40,basic_viewport_coords.y()-40,130,130);
//    scene->addRect(basic->shape());



//    centerOn(QPoint(100,100));
    basic->setFlag(QGraphicsItem::ItemIsFocusable);
    basic->setFocus();

    //https://doc.qt.io/qt-5/qtwidgets-graphicsview-collidingmice-example.html


    //mainloop
    loop_timer = new QTimer{this};
    //connect(loop_timer, &QTimer::timeout, this, &GameWindow::main_loop);
    connect(loop_timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    loop_timer->start(1000/30);


//    health_bar->setRect(0,0,100,20);
//    health_bar->setPos(100,200);
    HealthBar* health_bar = new HealthBar(basic);
//    health_bar->setRect(0,0,100,20);
    scene->addItem(health_bar);
//    QPointF healthpos;
//        healthpos.setX(health_bar->x());
//        healthpos.setY(health_bar->y());
//    qDebug() << basic->mapFromScene(healthpos);

    health_bar->setPos(healthpos + QPointF(0,70) - basic->mapFromScene(healthpos) );
    // Tank Graphic Test
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

//    for (int i = 0; i < MouseCount; ++i) {
//        TankGraphic *mouse = new TankGraphic;
//        mouse->setPos(::sin((i * 6.28) / MouseCount) * 200,
//                      ::cos((i * 6.28) / MouseCount) * 200);
//        scene->addItem(mouse);
//    }

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
//    float x = rect->x();
//    float y = rect->y();
//    centerOn(basic); // moved to Basic.cpp

    QPointF tankpos;
    tankpos.setX(basic->x());
    tankpos.setY(basic->y());

    // testing spinning tank
//    QPoint healthpos;
//    healthpos.setX(basic->x());
//    healthpos.setY(basic->y());
//    QPointF basic_viewport_coords = mapToScene(healthpos);

//    scene->addRect(basic_viewport_coords.x()-40,basic_viewport_coords.y()-40,130,130);
}

void GameWindow::spawn_loop() {
    for(int i = 0; i < 10000; i++) {
        Block* block = new Block(100,100,30,0,0,1,1,0);
        block->setRect(0,0,block->get_size(),block->get_size());
        block->setPos(rand()%1000000,rand()%1000000);
        scene->addItem(block);
    }
}
