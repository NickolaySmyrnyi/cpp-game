#ifndef REGION_H
#define REGION_H

#include <QDebug>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QPair>

#include "city.h"

// class which provides information of regions
// representing the parts of world
class Region : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
   public:
    // constructors
    Region(QGraphicsItem* parent = 0);

    // getters
    QString getName();
    QString getOwner();
    bool isFree();
    bool isWater();
    bool isDesert();
    bool isGround();
    bool isForest();
    bool isMountain();
    bool isOwned();
    City getCity();
    QPair<int, int> getCoordinates();

    // setters
    void setName(QString name);
    void setOwner(QString owner);
    void setFree(bool flag);
    void setWater(bool flag);
    void setDesert(bool flag);
    void setGround(bool flag);
    void setForest(bool flag);
    void setMountain(bool flag);
    void setOwned(bool flag);
    void setCity(City& city);
    void setCoordinates(int x, int y);

    // qt tools
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;

   private:
    // name of region and name of owner
    QString name_;
    QString owner_;

    // characteristics of the region
    bool free_ = true;
    bool owned_ = false;
    bool water_ = false;
    bool desert_ = false;
    bool ground_ = false;
    bool forest_ = false;
    bool mountain_ = false;

    // city at the region
    City city_;

    // coordinates of the region in the field
    QPair<int, int> coordinates_;
   signals:
    void signal(Region* region, bool flag = true);
};

#endif  // REGION_H
