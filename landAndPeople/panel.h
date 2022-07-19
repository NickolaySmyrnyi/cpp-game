#ifndef PANEL_H
#define PANEL_H

#include <QGraphicsTextItem>

#include "field.h"

class Events : public QGraphicsTextItem
{
   public:
    // constructors
    Events(QGraphicsItem* parent = 0);

    // getters
    bool isGameStarted();

    // qt tools
    void printYears();

   private:
    // if all starting regions are filled
    bool gameStarted_ = false;

   public slots:
    // changing text for starting regions procedure, start of the game
    // and for some actions
    void changeText(QString name);
    void messageAdded(QString message);
    void startGame();
};

#endif  // PANEL_H
