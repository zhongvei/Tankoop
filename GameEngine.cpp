#include "GameEngine.h"

#include <QTimer>

GameEngine::GameEngine(GameWindow* window, int wave, List *list, QString nameValue):
                       window(window), nameValue(nameValue)
{
    /* Create a Linked List to store Game History */
    if(wave == 0){
        waves_history = new List(nameValue);
    }
    else{
        /* Reload data from a specific wave */
        waves_history = list;
        waves_history->list_clear(waves_history,wave);

        /* Set the Coresponding Data Member to the Data from the Selected Wave */
        player = waves_history->selected_tank(waves_history);
        player->set_health(player->get_max_health());
        waves = waves_history->selected_wave(waves_history);
        max_enemies = waves_history->selected_num_of_enemies(waves_history);
        dynamic_cast<Basic *>(player)->set_parent(window);
        dynamic_cast<Basic *>(player)->reset_movement();

        reset_wave = true;
        original = false;

    }

    /* Play the Background Music */
    music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/Resources/sounds/inGameBackgroundMusic.mp3"));
    connect(music, &QMediaPlayer::stateChanged, [this](QMediaPlayer::State state) {
        if (state == QMediaPlayer::State::StoppedState){
            music->play();
        }
    });
    music->play();
}


/* Accessor */
int GameEngine::get_block_count() const {return block_count;}
int GameEngine::get_enemy_count() const {return enemy_count;}
int GameEngine::get_waves() const {return waves;}

/* Mutator */
void GameEngine::set_block_count(int block_count) {this->block_count = block_count;}
void GameEngine::set_enemy_count(int enemy_count) {this->enemy_count = enemy_count;}
void GameEngine::set_waves(int waves) {this->waves = waves;}

void GameEngine::run(){
    /* Create the Player that Starts with the Basic Class */
    if(player == nullptr)
        player = new Basic(window,this); //the original run (first run)

    /*
     * Set the Player
    */
    player->setRect(0,0,player->get_size(),player->get_size());
    player->setPos(350,250);
    window->scene->addItem(player);
    player->setFlag(QGraphicsItem::ItemIsFocusable);

    /*
     * Display the Name of the Player
    */
    player->name_item = new QGraphicsTextItem;
    player->set_name(waves_history->get_name());
    player->name_item->setPlainText(player->get_name());
    player->name_item->setDefaultTextColor(QColor("#008000"));
    player->name_item->setFont(QFont("Gill Sans MT", 16));
    window->scene->addItem(player->name_item);

    /*
     * Initiate the Main Timer
    */
    loop_timer = new QTimer{this};
    connect(loop_timer, &QTimer::timeout, this, &GameEngine::main_loop);
    connect(loop_timer, &QTimer::timeout, window->scene, &QGraphicsScene::advance);
    loop_timer->start(1000/60); // 60 fps

    /* Timer for the Total Time Alive in Ending Statitics */
    elapsed_timer.start();

    /* Create the Health Bar */
    player->create_heatlh_bar(window->scene);
    window->scene->addItem(player->get_health_bar());

    /* The HUD */
    hud = new Hud(window, player,this);
}

void GameEngine::main_loop() {
    if(!game_over()){
        player->check_collision();
        hud->update_value();

        if(finish_wave){
            if(!reset_wave){
                /* Create a new node and store it in the linked list */
                waves_history->list_push_back(waves_history, waves_history->create_node(dynamic_cast<Basic*>(player), max_enemies, waves)); //call list_delete.. but where?
            }
            entity_spawn();
            finish_wave = false;
            reset_wave = false;
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
            if (max_enemies == 5)
                max_enemies = 3;
            else
                max_enemies += 1;

            waves++;
        }
    } else {
        hud->hide();
        loop_timer->stop();
        delete loop_timer;
        delete player->name_item;
        player->name_item = nullptr; // move to wilsons code part

        /* Create MainWindow::EndGameWindow */
        EndGameWindow* endWindow = new EndGameWindow(waves_history);
        endWindow->setWindowTitle("TankOOP");

        /*
         * Calculate Ending Statistics
        */
        QString player_xp = QString::number(player->get_xp());
        QString player_class = player->TYPE_textstr[static_cast<int>(player->get_type())];
        QString player_subtank = player->SUBTANK_textstr[static_cast<int>(player->get_subtank())];
        QString player_time_alive = QString::number(elapsed_timer.elapsed()/1000);
        endWindow->endGameStats(player_xp, player_class, player_subtank, player_time_alive);

        /* Add player's stats to leaderboard */
        append_cumulativeEnemyLists(player->get_name(), player->get_xp());
        ensureMin_cumulativeEnemyLists(); // sort list from highest to lowest score

        if(original){
            delete player->music;
            delete player;
            player = nullptr;
        }

        endWindow->endGameLeaderboard(cumulativeEnemyNames[0],cumulativeEnemyNames[1],cumulativeEnemyNames[2],
                cumulativeEnemyNames[3],cumulativeEnemyNames[4],cumulativeEnemyScores[0],cumulativeEnemyScores[1],
                cumulativeEnemyScores[2],cumulativeEnemyScores[3],cumulativeEnemyScores[4]);

        endWindow->show();

        music->stop();
        delete music;


        /* Clear all the entity inside map when the game is over */
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

        /* Close this window */
        window->close();
    }
}

/* Spawning the Enemies */
void GameEngine::spawn_enemies_loop(){
    while(get_enemy_count() < max_enemies) {

        Enemy *enemy = new Enemy(this, 500,1000,100);
        enemy->setPos(QRandomGenerator::global()->bounded(GameWindow::WINDOW_WIDTH),
                      QRandomGenerator::global()->bounded(GameWindow::WINDOW_HEIGHT));
        enemy->setRect(0,0,enemy->get_size(),enemy->get_size());
        enemy->get_attack_area()->setPos(enemy->x() - enemy->get_size() * (enemy->get_attack_scale()-1)/2,
                                         enemy->y() - enemy->get_size() * (enemy->get_attack_scale()-1)/2);
        enemy->get_sight_area()->setPos(enemy->x() - enemy->get_size() * (enemy->get_sight_scale()-1)/2,
                                        enemy->y() - enemy->get_size() * (enemy->get_sight_scale()-1)/2);
        enemy->create_heatlh_bar(window->scene);

        enemy->name_item = new QGraphicsTextItem;
        enemy->name_item->setPlainText(enemy->get_name());
        enemy->name_item->setFont(QFont("Gill Sans MT", 16));
        window->scene->addItem(enemy->name_item);

        window->scene->addItem(enemy);
        window->scene->addItem(enemy->get_health_bar());
        window->scene->addItem(enemy->get_attack_area());
        window->scene->addItem(enemy->get_sight_area());
        set_enemy_count(get_enemy_count()+1);
    }
}

void GameEngine::spawn_block_loop() {
    while (get_block_count() < 50) {

        /* Randomize the location of the spawned block */
        Block* block = new Block(100,100,30,0,0,10,1);
        block->setRect(0,0,block->get_size(),block->get_size());
        block->setPos(QRandomGenerator::global()->bounded(GameWindow::WINDOW_WIDTH),
                      QRandomGenerator::global()->bounded(GameWindow::WINDOW_HEIGHT));

        QTransform transform;
        transform.translate(block->get_size()/2,block->get_size()/2);
        transform.rotate(QRandomGenerator::global()->bounded(360));
        transform.translate(-(block->get_size()/2),-(block->get_size()/2));
        block->setTransform(transform);
        block->setBrush(Qt::red);

        /* Adding block object into the Game Window */
        window->scene->addItem(block);

        /*
         * Removing all stacked blocks
         */
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
    return (player->get_health() <= 0 ? true : false);
}

// if enemy dies, emit signal to SLOT enemyDied(QString name, int score)
void GameEngine::enemyDied(QString name, int score) {
    qDebug()<<"enemy died";
    append_cumulativeEnemyLists(name, score);
}

/*
 * Ensures that QVector types cumulativeEnemyNames and cumulativeEnemyScores
 * has a minimum size of 5 for leaderboard displaying in end screen.
*/
void GameEngine::ensureMin_cumulativeEnemyLists() {
    if (cumulativeEnemyScores.size() < 5) {
        int minimum = 5 - cumulativeEnemyScores.size();
        for (int i = 0; i < minimum; i++) {
            cumulativeEnemyNames.push_back(QString("N/A"));
            cumulativeEnemyScores.push_back(0);
        }
    }
}

/*
 * Appends name and score to (QVector) cumulativeEnemyNames and cumulativeEnemyScores
 * respectively, adding them to a sorted list.
*/
void GameEngine::append_cumulativeEnemyLists(QString name, int score) {
    if (cumulativeEnemyScores.size() == 0) {
        cumulativeEnemyNames.append(name);
        cumulativeEnemyScores.append(score);
        return;
    }
    for (int i = 0; i < cumulativeEnemyScores.size(); ++i) {
        if (score > cumulativeEnemyScores[i]) {
            cumulativeEnemyNames.insert(i,name);
            cumulativeEnemyScores.insert(i,score);
            return;
        }
    }
}
