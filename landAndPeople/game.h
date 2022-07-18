#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QInputDialog>
#include <QKeyEvent>

#include "panel.h"

// class which provides game functionality
// and a sequence of events
class Game : public QGraphicsView
{
   public:
    // constructors
    Game(QWidget* parent = 0);
    void keyPressEvent(QKeyEvent* event) override;
    void makeAction();
   public slots:
    // field with game and panel with messages
    Field* field;
    Events* panel;

    // qt tools
    QGraphicsScene* scene;

    // vector of colors for players
    QVector<QColor> colors = {Qt::green, Qt::red,  Qt::magenta, Qt::yellow,
                              Qt::cyan,  Qt::gray, Qt::darkRed, Qt::darkGreen};

    // adding names for region and (depending on flag) for city in region
    void addNames(Region* region, bool flag = true);
};

#endif  // GAME_H
