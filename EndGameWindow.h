#ifndef ENDGAMEWINDOW_H
#define ENDGAMEWINDOW_H

#include "List.h"

#include <QMainWindow>
namespace Ui { class EndGameWindow; }

class EndGameWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit EndGameWindow(List *list, QWidget *parent = nullptr);
    void homeScreen();
    void endGameStats(QString player_xp, QString player_class, QString player_subtank, QString player_time_alive);
public slots:
    void start_button_clicked();
    void home_screen_clicked();
    void quit_game();
private:
    List *list;
    Ui::EndGameWindow *ui;

};


#endif // ENDGAMEWINDOW_H
