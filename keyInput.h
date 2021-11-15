
//#include <QMainWindow>
//#include <QGraphicsItem>

//#ifndef KEYINPUTS_H
//#define KEYINPUTS_H

//class keyInput : public QGraphicsObject
//{
//    Q_OBJECT

//public:
//    keyInput(int focusedPlayerId = 0, QGraphicsObject *parent = nullptr);
//    QRectF boundingRect() const override;
//    QPainterPath shape() const override;
//    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
//    void keyPress(QKeyEvent *event);
//    void keyRelease(QKeyEvent *event);

//private:
//    QHash<int, QList<int>> playersKeys;
//    // The same is in player.h
//    void setPlayerKeys(int focusedPlayerId);
//    enum PlayerMovesEnum : int {up = 0, right = 1, down = 2, left = 3};

//signals:
//    void playerKeyToggle(int playerId, int direction, bool value);
//};

//#endif // KEYINPUTS_H
