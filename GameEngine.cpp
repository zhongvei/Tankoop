#include "GameEngine.h"
#include "GameEntity/Basic.h"
#include "GameEntity/Enemy.h"
#include "GameEntity/Bullet.h"
#include "GameEntity/HealthBar.h"
#include "EndGameWindow.h"

#include <QRandomGenerator>
#include <QMessageBox>
#include <QTimer>



GameEngine::GameEngine(GameWindow* window, QGraphicsScene* scene, int wave, List *list): window(window), scene(scene)
{
    if(wave == 0){
        qDebug() << "CREATING A NEW LIST";
        waves_history = new List();
    }
    else{
        waves_history = list;
        waves_history->list_clear(waves_history,wave);
        player = waves_history->selected_tank(waves_history);
        qDebug() << "3 " << player->get_vx();
        player->set_type(waves_history->return_type(waves_history));
        qDebug() << "4 " << player->get_vx();
        dynamic_cast<Basic *>(player)->set_parent(window);
        waves = waves_history->selected_wave(waves_history);
        max_enemies = waves_history->selected_num_of_enemies(waves_history);
    }
}

/* MUTATOR */
void GameEngine::set_enemy_count(int enemy_count) {this->enemy_count = enemy_count;}
void GameEngine::set_block_count(int block_count) {this->block_count = block_count;}
void GameEngine::set_waves(int waves) {this->waves = waves;}

/* ACCESOR */
int GameEngine::get_block_count() const {return block_count;}
int GameEngine::get_enemy_count() const {return enemy_count;}
int GameEngine::get_waves() const {return waves;}

void GameEngine::run(){
    /* CREATE THE PLAYER, STARTS WITH THE BASIC CLASS */
    if(player == nullptr){
        player = new Basic(window);
    }
    player->setRect(0,0,player->get_size(),player->get_size());
    player->setPos(350,250);
    window->scene->addItem(player);
    player->setFlag(QGraphicsItem::ItemIsFocusable);

    /* INITIATE THE MAIN TIMER */
    loop_timer = new QTimer{this};
    connect(loop_timer, &QTimer::timeout, this, &GameEngine::main_loop);
    connect(loop_timer, &QTimer::timeout, window->scene, &QGraphicsScene::advance);
    loop_timer->start(1000/60); // 60 fps

    /* TIMER FOR TOTAL TIME ALIVE IN ENDING STATISTICS */
    elapsed_timer.start();

    /* ENEMY SPAWNER */
//    enemy_timer = new QTimer{this};
//    connect(enemy_timer, &QTimer::timeout, this, &GameEngine::spawn_enemies);
//    enemy_timer->start(10000); //adding new enemy every 100 seconds
//    spawn_enemies_loop();

    /* CREATE HEALTH BAR */
    player->create_heatlh_bar(window->scene);
    window->scene->addItem(player->get_health_bar());

//    entity_spawn_timer = new QTimer{this};
//    connect(entity_spawn_timer,&QTimer::timeout,this,&GameEngine::entity_spawn);
//    loop_timer->start(5000);

    //spawn the block
//    spawn_block_loop();

    /* The HUD */
    hud = new Hud(window, player);
}

void GameEngine::main_loop() {
    if(!game_over()){
        player->check_collision();
        hud->update_value();
        if(finish_wave){
            qDebug() << "WAVES " << waves;
            qDebug() << "1 "<< player->get_vx();
            waves_history->list_push_back(waves_history, waves_history->create_node(dynamic_cast<Basic*>(player), player->get_type(), max_enemies, waves)); //call list_delete.. but where?
            qDebug() << "2 " << player->get_vx();
            entity_spawn();
            finish_wave = false;
        }
        if(get_enemy_count() == 0){
            QList<QGraphicsItem *> list = this->window->items();
            for(int i = 0; i < list.size(); i++){
                if(typeid(*(list[i])) == typeid (Block)){
                    delete list[i];
                    list[i] = nullptr;
                }
            }
            set_block_count(0);
            finish_wave = true;
            max_enemies += 1;
            waves++;
        }
    } else {
        qDebug() << "gameover";
        hud->hide();
        loop_timer->stop();
        delete loop_timer;

        //QMessageBox* msg_box = new QMessageBox(window);
        //msg_box->setText("GAMEOVER!");
        //msg_box->show();

        /* Create MainWindow::EndGameWindow */
        qDebug() << "WAVE HISTORY WORKING " << waves_history->selected_wave(waves_history);
        EndGameWindow* endWindow = new EndGameWindow(waves_history);
        endWindow->setWindowTitle("TankOOP");

        /* Calculate Ending Statistics */
        QString player_xp = QString::number(player->get_xp());
        QString player_class = player->TYPE_textstr[static_cast<int>(player->get_type())];
        QString player_subtank = player->SUBTANK_textstr[static_cast<int>(player->get_subtank())];
        QString player_time_alive = QString::number(elapsed_timer.elapsed()/1000);
        endWindow->endGameStats(player_xp, player_class, player_subtank, player_time_alive);
        delete player;
        player = nullptr;
        endWindow->show();

        // TODO: stop the game when game ends
        // (not really necessary, takes too much time to find out how to delete all things)
        // just cannot do play again after player just died, or else severe memory leak
        //scene->clear();

        QList<QGraphicsItem *> list = this->window->items();
        bool skip = false;
        int skip_count = 0;
        for(int i = 0; i < list.size(); i++){

            // To avoid double deletion for the enemy's properties
            if(skip){
                skip_count++;
                if(skip_count == 4){
                    skip_count = 0;
                    skip = false;
                }
                continue;
            }

            if(typeid(*(list[i])) == typeid (Block)){
                delete list[i];
                list[i] = nullptr;
            }
            else if(typeid(*(list[i])) == typeid (Bullet)){
                delete list[i];
                list[i] = nullptr;
            }

            else if(typeid(*(list[i])) == typeid (QGraphicsLineItem)){
                delete list[i];
                list[i] = nullptr;
            }

            else if(typeid(*(list[i])) == typeid (Enemy)){
                delete list[i];
                list[i] = nullptr;
                skip = true;
            }

        }

        window->close();
    }
}

void GameEngine::spawn_enemies_loop(){
    while(get_enemy_count() < max_enemies) {
//        qDebug() << "NEW ENEMY HAS BEEN ADDED TO THE MAP";

        Enemy *enemy = new Enemy(this, 500,1000,100); // multiple of 50

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

        set_enemy_count(get_enemy_count()+1);
    }
}

void GameEngine::spawn_block_loop() {
    while (get_block_count() < 50) {
        Block* block = new Block(100,100,30,0,0,10,1,7);
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
            if((typeid(*list[i]) == typeid(Block)) || (typeid(*list[i]) == typeid(Tank))) {
                window->scene->removeItem(list[i]);
                delete list[i];
                list[i] = nullptr;
            }
        }
        if(block->x() < diagonal || block->x() > (GameWindow::WINDOW_WIDTH- diagonal)||
           block->y() < diagonal || block->y() > (GameWindow::WINDOW_HEIGHT- diagonal)) {
            window->scene->removeItem(block);
            delete block;
        }


        set_block_count(get_block_count()+1);

    }

}

void GameEngine::entity_spawn()
{
    spawn_block_loop();
    spawn_enemies_loop();
}

bool GameEngine::game_over() {
    if(player->get_health() <= 0) {
        return true;
    }
    return false;
}
