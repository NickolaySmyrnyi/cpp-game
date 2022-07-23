#include "panel.h"

Events::Events(QGraphicsItem *parent) : QGraphicsTextItem(parent)
{
    setPos(0, 0);
    setFont(QFont("times", 12));
}

bool Events::isGameStarted() { return gameStarted_; }

void Events::printYears()
{
    // number of years increase after space pressed
    static int spaces = 0;

    if (gameStarted_)
    {
        setPlainText("Press \"SPACE\"\nYear " + QString::number(spaces) +
                     "\n\n");
    }

    ++spaces;
}

void Events::changeText(QString name)
{
    setPlainText("Choose the starting region\nof " + name);
}

void Events::messageAdded(QString message)
{
    setPlainText(toPlainText() + message + "\n\n");
}

void Events::startGame()
{
    gameStarted_ = true;
    setPlainText("Press \"SPACE\"\n");
}
