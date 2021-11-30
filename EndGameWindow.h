#ifndef ENDGAMEWINDOW_H
#define ENDGAMEWINDOW_H

#include "List.h"

#include <QMainWindow>
namespace Ui { class EndGameWindow; }

class EndGameWindow : public QMainWindow
{
    Q_OBJECT

private:
    List *list;
    Ui::EndGameWindow *ui;

public:

    /*
     *  @funct: Constructs the EndGame Window and set the end game interface with all of its attributes.
     *
     *  @param: list: the list that stores the game history from the game engine.
     *          parent: to access the widget in the game window interface. Default to nullptr.
     *
     *  @return: N/A
     */
    explicit EndGameWindow(List *list, QWidget *parent = nullptr);

    /*
     *  @funct: Function to direct the user to the main window of the game. Deallocates the memories of the
     *          current linked list.
     *
     *  @param: N/A
     *  @return: N/A
     */
    void homeScreen();

    /*
     *  @funct: Function to display the end game statistics.
     *
     *  @param: player_xp: the amount of xp that the user has accumulated.
     *          player_class: the tank class that the user choose
     *          player_subtank: the subtank that the user choose.
     *          player_time_alive: the duration of how long the player can survive the game.
     *
     *  @return: N/A
     */
    void endGameStats(QString player_xp, QString player_class, QString player_subtank, QString player_time_alive);

    /*
     *  @funct: Function to show the leaderboard of the top 5 player in the game.
     *
     *  @param: name_x(int): the top x player with the highest score
     *          score_x(int): the amount of score of name_x player.
     *
     *  @return: N/A
     */
    void endGameLeaderboard(QString name_1,QString name_2,QString name_3,QString name_4,QString name_5,
                            int score_1, int score_2, int score_3, int score_4, int score_5);
public slots:
    void start_button_clicked();
    void home_screen_clicked();
    void increase();
    void decrease();
    void reset();
    void quit_game();


};


#endif // ENDGAMEWINDOW_H
