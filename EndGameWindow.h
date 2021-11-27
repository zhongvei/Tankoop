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
public slots:
    void home_screen_clicked();
private:
    Ui::EndGameWindow *ui;

};


#endif // ENDGAMEWINDOW_H
