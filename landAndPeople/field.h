#ifndef FIELD_H
#define FIELD_H

#include <stdlib.h>

#include <QGraphicsEllipseItem>
#include <QGraphicsPolygonItem>
#include <QMessageBox>
#include <QPointF>
#include <QPolygonF>

#include "player.h"

// class which provides the field
// representing world and creates it
class Field : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
   public:
    // constructors
    Field(QGraphicsItem* parent = 0);

    // function to make field visible and be created
    void appear();

    // functions for drawing different items in regions
    void drawWater(Region* water);
    void drawMountain(Region* mountain);
    void drawCity(Region* city);

    // algorithms for country spreading at the start of the game
    Region* findRegion1(Region* region, bool flag = true);
    Region* findRegion2(Region* region, bool flag = true);
    void findNewRegion();

    // checking if all the regions are filled
    bool isNotFree();

    // setters
    void addPlayer(Player& player);

    // getters
    Player getPlayer(int index);

   private:
    // the number of regions which are owned, water
    int notFreeRegions_ = 0;

    // all players and regions in the game
    QVector<Player> playerVector_;
    QVector<QVector<Region*>> regionVector_;

    // qt tools
    QGraphicsPolygonItem* mount_;
    QGraphicsEllipseItem* ellipse_;
    QMessageBox* message_;

   private slots:
    // create first regions
    void setStartingRegions(Region* region);

    // get information about existing regions
    void getRegionInformation();

   signals:
    void signal1(QString name);
    void signal2(Region* region, bool flag = true);
    void signal3();
    void signal4(QString name);
};

#endif  // FIELD_H
