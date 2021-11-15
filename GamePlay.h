//#ifndef GAMEPLAY_H
//#define GAMEPLAY_H

//#include <QMainWindow>
//#include <QGraphicsItem>
//#include <QGraphicsView>
//#include <QGraphicsScene>
//#include <QSet>
//#include <QTimer>
////#include "candy.h"
//#include "Player.h"
//#include "keyInput.h"
//#include "dataLoader.h"
//#include "Tile.h"
////#include "tilecandyplacement.h"
////#include "tcpclient.h"
//#include <QElapsedTimer>

//class GamePlay : public QGraphicsScene
//{
//    Q_OBJECT

//public:
//    GamePlay(QGraphicsScene *parent = nullptr);
//    ~GamePlay();
//    void keyPress(QKeyEvent *event);
//    void keyRelease(QKeyEvent *event);
//    QList<Tile*> tilesNearby(QString layer, int x, int y);
////    QList<Candy *> candiesNearby(int x, int y);
////    QList<TileCandyPlacement *> getTileCandyPlacementList();
//    bool hasPlayerAnyCandyValid(int playerId);

//    enum PlayerMovesEnum : int {up = 0, right = 1, down = 2, left = 3};

//private:
////    TcpClient *tcpClient;
//    QTimer *playerRefresh;
//    QElapsedTimer *playerRefreshDelta;
//    QTimer *serverRollback;
//    QTimer *gameTimer;
//    QHash<int, Player*> players;
////    QHash<int, Candy*> candies;
////    QList<TileCandyPlacement*> tileCandyPlacements;
//    // la string est le nom des layers
//    QHash<QString, QList<Tile*>> tiles;
//    keyInput *keyboardInputs;
//    DataLoader *dataLoader;

//    bool startBool;
//    QHash<int, int> scores;

//    void setCustomSceneRect();
//    void placeTiles();
//    void refreshEntities();
////    void placeTilesCandyPlacement();
////    void setupMultiplayerGame();
//    void setupLocalGame(int nbPlayers);
////    void placeBosses();

//private slots:
//    void sendRollback();
//    void receiveRollback(double playerX, double playerY, QHash<int, QPointF> candies, int playerDescriptor);
////    void spawnCandy(int candyType, int candySize, int nbPoints, int tilePlacementId, int candyId);
////    void playerStealsCandies(int candyIdStartingFrom, int playerWinningId);
////    void playerValidateCandies(int playerId);
////    void playerPickedUpCandyMulti(int descriptor, int candyId);
////    void deleteCandy(int id, int playerId);
//    void gameEnd();

//public slots:
//    void startGame(QString terrainFileName, int nbPlayers, bool isMultiplayer);//, TcpClient *tcpClient);

//signals:
//    void rollbackToServer(QPointF playerPos, QHash<int, QPointF> candiesTaken);
////    void playerStealCandies(int candyIdStartingFrom, int playerWinningId);
////    void teamsPointsChanged(int nbPointsRed, int nbPointsBlack);
//    void showEndScreen(int teamWinner);

//};


//#endif // GAMEPLAY_H
