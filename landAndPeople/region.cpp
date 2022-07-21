#include "region.h"

Region::Region(QGraphicsItem* parent) : QGraphicsRectItem(parent)
{
    // creating region as a rectangle
    setRect(0, 0, 50, 50);
}

QString Region::getName() { return name_; }

QString Region::getOwner() { return owner_; }

bool Region::isFree() { return free_; }

bool Region::isWater() { return water_; }

bool Region::isDesert() { return desert_; }

bool Region::isGround() { return ground_; }

bool Region::isForest() { return forest_; }

bool Region::isMountain() { return mountain_; }

bool Region::isOwned() { return owned_; }

City Region::getCity() { return city_; }

QPair<int, int> Region::getCoordinates() { return coordinates_; }

void Region::setName(QString name) { name_ = name; }

void Region::setOwner(QString owner) { owner_ = owner; }

void Region::setFree(bool flag) { free_ = flag; }

void Region::setWater(bool flag) { water_ = flag; }

void Region::setDesert(bool flag) { desert_ = flag; }

void Region::setGround(bool flag) { ground_ = flag; }

void Region::setForest(bool flag) { forest_ = flag; }

void Region::setMountain(bool flag) { mountain_ = flag; }

void Region::setOwned(bool flag) { owned_ = flag; }

void Region::setCity(City& city) { city_ = city; }

void Region::setCoordinates(int x, int y)
{
    coordinates_ = QPair<int, int>(x, y);
}

void Region::setLandscapeColor()
{
    if (desert_)
    {
        setBrush(Qt::yellow);
        return;
    }
    if (ground_)
    {
        setBrush(Qt::gray);
        return;
    }
    if (forest_)
    {
        setBrush(Qt::green);
        return;
    }
    if (mountain_)
    {
        setBrush(Qt::white);
        return;
    }
}

QString Region::getInfo()
{
    QString result = "";
    result += "Name: " + name_ + '\n';
    if (owned_) result += "Owner: " + owner_ + '\n';
    if (city_.getName() != "") result += "City: " + city_.getName() + '\n';
    result += "Landscape type: ";
    if (water_)
        result += "water";
    else if (mountain_)
        result += "mountain";
    else if (ground_)
        result += "ground";
    else if (forest_)
        result += "forest";
    else
        result += "desert";
    return result;
}

void Region::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
    emit signal(this);
}
