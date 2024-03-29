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

    // setters
    void addPlayer(Player& player);
    void setLandscape(bool flag);

    // getters
    Player getPlayer(int index);
    bool isLandscape();

    // function to make field visible and be created
    void appear();

    // count the number of players
    int countPlayers();

    // actions
    int changeRelations(int index1, int index2, int bonus);

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

    // change the map appearence
    void becomeLandscape();
    void becomePolitical();

   private:
    // the number of regions which are owned, water
    int notFreeRegions_ = 0;

    bool landscape_ = false;

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
    void getRegionInformation(Region* region);

   signals:
    void signal1(QString name);
    void signal2(City& city, Region* region, bool flag = true);
    void signal3();
    void signal4(QString name);
};

#endif  // FIELD_H
