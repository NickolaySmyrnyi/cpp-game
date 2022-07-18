#include <QApplication>

#include "game.h"

int main(int argc, char* argv[])
{
    // starting application and game
    srand(time(NULL));
    QApplication a(argc, argv);
    Game game;
    return a.exec();
}
