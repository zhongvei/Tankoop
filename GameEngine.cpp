#include "GameEngine.h"
#include "GameEntity/Basic.h"
#include "GameEntity/Enemy.h"
#include "GameEntity/HealthBar.h"

#include <QRandomGenerator>
#include <QMessageBox>
#include <QTimer>



GameEngine::GameEngine(GameWindow* window): window(window)
{}

/* MUTATOR */
void GameEngine::increase_block_count() {this->block_count++;}
void GameEngine::decrease_block_count() {this->block_count--;}

void GameEngine::increase_enemy_count() {this->enemy_count++;}
void GameEngine::decrease_enemy_count() {this->enemy_count--;}

/* ACCESOR */
int GameEngine::get_block_count() const {return block_count;}
int GameEngine::get_enemy_count() const {return enemy_count;}

void GameEngine::run(){
    /* CREATE THE PLAYER, STARTS WITH THE BASIC CLASS */
    player = new Basic(window);
    player->setRect(0,0,player->get_size(),player->get_size());
    player->setPos(350,250);
    window->scene->addItem(player);
    player->setFlag(QGraphicsItem::ItemIsFocusable);

    /* INITIATE THE MAIN TIMER */
    loop_timer = new QTimer{this};
    connect(loop_timer, &QTimer::timeout, this, &GameEngine::main_loop);
    connect(loop_timer, &QTimer::timeout, window->scene, &QGraphicsScene::advance);
    loop_timer->start(1000/60); // 60 fps

    /* ENEMY SPAWNER */
    enemy_timer = new QTimer{this};
    connect(enemy_timer, &QTimer::timeout, this, &GameEngine::spawn_enemies);
    enemy_timer->start(10000); //adding new enemy every 100 seconds
    spawn_enemies();

    /* CREATE HEALTH BAR */
    player->create_heatlh_bar(window->scene);
    window->scene->addItem(player->get_health_bar());

    //spawn the block
    spawn_loop();
    qDebug()<<get_block_count();

    /* The HUD */
    hud = new Hud(window, player);
}

void GameEngine::main_loop() {
    if(!game_over()){
        player->check_collision();
        hud->update_value();
    } else {
        hud->hide();
        loop_timer->stop();
        QMessageBox* msg_box = new QMessageBox(window);
        msg_box->setText("GAMEOVER!");
        msg_box->show();
    }
}

void GameEngine::spawn_enemies(){
    if(get_enemy_count() <= 5) {
        qDebug() << "NEW ENEMY HAS BEEN ADDED TO THE MAP";
        Enemy *enemy = new Enemy(500,100); // multiple of 50

        enemy->setPos(QRandomGenerator::global()->bounded(GameWindow::WINDOW_WIDTH),
                      QRandomGenerator::global()->bounded(GameWindow::WINDOW_HEIGHT));
        enemy->setRect(0,0,enemy->get_size(),enemy->get_size());
        //double scale = enemy->get_size() / enemy->get_range();
        enemy->get_attack_area()->setPos(enemy->x() - enemy->get_size() * (enemy->get_attack_scale()-1)/2,
                                         enemy->y() - enemy->get_size() * (enemy->get_attack_scale()-1)/2);
        enemy->get_sight_area()->setPos(enemy->x() - enemy->get_size() * (enemy->get_sight_scale()-1)/2,
                                        enemy->y() - enemy->get_size() * (enemy->get_sight_scale()-1)/2);
        enemy->create_heatlh_bar(window->scene);
        window->scene->addItem(enemy->get_health_bar());

        window->scene->addItem(enemy);
        window->scene->addItem(enemy->get_attack_area());
        window->scene->addItem(enemy->get_sight_area());
        increase_enemy_count();
    }
}

void GameEngine::spawn_loop() {
    for(int number = 0; number < 300; number++) {
        Block* block = new Block(100,100,30,0,0,10,1,0);
        block->setRect(0,0,block->get_size(),block->get_size());
        block->setPos(QRandomGenerator::global()->bounded(GameWindow::WINDOW_WIDTH),
                      QRandomGenerator::global()->bounded(GameWindow::WINDOW_HEIGHT));
        QTransform transform;
        transform.translate(block->get_size()/2,block->get_size()/2);
        transform.rotate(QRandomGenerator::global()->bounded(360));
        transform.translate(-(block->get_size()/2),-(block->get_size()/2));
        block->setTransform(transform);
        block->setBrush(Qt::red);
        window->scene->addItem(block);
        QList<QGraphicsItem *> list = block->collidingItems();
        float diagonal = hypot(block->get_size(),block->get_size());
        for(int i =0; i< list.size(); i++) {
            if((typeid(*list[i]) == typeid(Block)) || (typeid(*list[i]) == typeid(Tank)) ) {
                window->scene->removeItem(list[i]);
                delete list[i];
            }
        }
        if(block->x() < diagonal || block->x() > (GameWindow::WINDOW_WIDTH- diagonal)||
           block->y() < diagonal || block->y() > (GameWindow::WINDOW_HEIGHT- diagonal)) {
            window->scene->removeItem(block);
            delete block;
        }
        increase_block_count();
    }
}

bool GameEngine::game_over() {
    if(player->get_health() <= 0) {
        qDebug()<<"gameover";
        return true;
    }
    return false;
}
