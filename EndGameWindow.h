#ifndef ENDGAMEWINDOW_H
#define ENDGAMEWINDOW_H

#include <QMainWindow>
namespace Ui { class EndGameWindow; }

class EndGameWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit EndGameWindow(QWidget *parent = nullptr);
    void homeScreen();
    void endGameStats(QString player_xp, QString player_class, QString player_subtank, QString player_time_alive);
    void endGameLeaderboard(QString name_1,QString name_2,QString name_3,QString name_4,QString name_5,
                            int score_1, int score_2, int score_3, int score_4, int score_5);
public slots:
    void home_screen_clicked();
private:
    Ui::EndGameWindow *ui;

};


#endif // ENDGAMEWINDOW_H
