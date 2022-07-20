#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QInputDialog>
#include <QKeyEvent>
#include <QPushButton>

#include "panel.h"

// class which provides game functionality
// and a sequence of events
class Game : public QGraphicsView
{
   public:
    // constructors
    Game(QWidget* parent = 0);

    // making some actions of some countries every year
    void makeAction();

    // qt tools
    void keyPressEvent(QKeyEvent* event) override;
    QGraphicsScene* scene;
    QPushButton* button;

   private:
    // field with game and panel with messages
    Field* field_;
    Events* panel_;

    // vector of colors for players
    QVector<QColor> colors_ = {Qt::green,   Qt::red,      Qt::magenta,
                               Qt::yellow,  Qt::cyan,     Qt::darkMagenta,
                               Qt::darkRed, Qt::darkGreen};
   public slots:
    // adding names for region and (depending on flag) for city in region
    void addNames(City& city, Region* region, bool flag = true);
    void showLandscape();
};

#endif  // GAME_H
