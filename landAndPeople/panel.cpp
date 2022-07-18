#include "panel.h"

Events::Events(QGraphicsItem *parent) : QGraphicsTextItem(parent)
{
    setPos(1000, 0);
    setFont(QFont("times", 12));
}

bool Events::isGameStarted() { return gameStarted_; }

void Events::printYears()
{
    static int spaces = 0;

    if (gameStarted_) qDebug() << "genious";
}

void Events::changeText(QString name)
{
    setPlainText("Choose the starting region\nof " + name);
}

void Events::regionAdded(QString name)
{
    setPlainText(name + " added new region");
}

void Events::startGame()
{
    gameStarted_ = true;
    setPlainText("Press \"SPACE\"");
}
