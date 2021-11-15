#include <QApplication>
#include "MainWindow.h"

int main(int argc, char **argv)
{
    srand(time(NULL));
    QApplication app (argc, argv);
    MainWindow window;
    window.setWindowTitle("TankOOP");
    //window.setWindowIcon(QIcon(":/Resources/brand/schoolboybattle-icon.ico"));
    window.show();
    return app.exec();
}
