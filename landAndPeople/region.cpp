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

void Region::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
    emit signal(this);
}
