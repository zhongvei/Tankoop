
//#include "dataLoader.h"
//#include "Tile.h"
////#include "candy.h"
//#include <QMainWindow>
//#include <QGraphicsItem>
//#include <QGraphicsView>
//#include <QGraphicsScene>
//#include <QVector2D>

//#ifndef PLAYER_H
//#define PLAYER_H

//class Player : public QGraphicsObject
//{
//    Q_OBJECT

//public:
//    Player(int team, DataLoader *dataLoader);
//    Player(
//            int id,
//            int team,
//            int gender,
//            QString username,
//            DataLoader *dataLoader,
//            QGraphicsObject *parent = nullptr);
//    QRectF boundingRect() const override;
//    QPainterPath shape() const override;
//    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
//    void refresh(double delta, int socketDescriptor);
////    QList<int> looseCandies(int candyStolenId);
////    QList<int> getCandiesTaken();
////    void pickupCandyMulti(int candyId);
////    void prependCandiesTaken(QList<int> candiesGained);
//    int getId();
//    int getTeam();
//    void protectQueue();
////    void deleteCandy(int candyId);
////    void setMainPlayerInMulti();

//    // En protected se trouve les variables et
//    // fonctions nécessaires pour la classe Boss
//protected:
//    enum Team : int {red = 0, black = 1};
////    enum Animations : int {idle = 0, run = 1};
//    enum Facing {facingLeft, facingRight};
//    Team team;
//    Facing facing;
////    typedef struct Animations_s {
////        QTimer *timer;
////        int frameIndex;
////        DataLoader::PlayerAnimationsStruct *sharedDatas;
////    } AnimationsLocalStruct;
////    QHash<Animations, AnimationsLocalStruct*> animationsLocal;
//    DataLoader *dataLoader;
//    QTimer *queueProtected;

//    void setZIndex(int yToAdd);
////    void animationNextFrame();
////    void setAnimation(Animations a);

//private:
//    enum Gender : int {girl = 0, boy = 1};
//    enum PlayerMoves {moveUp, moveRight, moveDown, moveLeft};

//    Gender gender;
////    Animations currentAnimation;
////    QList<int> IdsCandiesTaken;
//    QList<QGraphicsTextItem *> textsItems;
//    QGraphicsTextItem *username;
//    int id;                 // En solo : int incrémentatif
//    // En multi : le SocketDescriptor
//    bool moves[4] = {false, false, false, false};
//    bool atSpawn;
////    bool isMainPlayerMulti;

//    //void refreshTakenCandies();
//    void move(QVector2D vector, bool inverted = false);
//    bool collideWithWalls(QVector2D movingVector);
//    void collideWithCandy();
//    void collideWithSpawn();
//    void showTextCandiesUpdated(int nbUpdated);
//    int getTextXToCenter(QGraphicsTextItem *text);

//    QVector2D calculateMovingVector(double delta);
//    QVector2D calculateAnswerVector(QVector2D movingVector);
////    QPixmap *getAnimationByTeamAndGender(QString name);
////    Animations getAnimationType();
//    Player::Facing getFacing();
//    void loadAnimations();
////    Player::AnimationsLocalStruct *setupAnimation(DataLoader::PlayerAnimationsStruct* sharedDatas);
//    void setUsername(QString username);

//public slots:
//    void keyMove(int playerId, int direction, bool value);

//signals:
////    void isCandyFree(int candyId);
////    void stealCandies(int candyIdStartingFrom, int playerWinningId);
//    void validateCandies(int id);
//    bool arePlayerTakenCandiesValidated(int id);
//};

//#endif // PLAYER_H
