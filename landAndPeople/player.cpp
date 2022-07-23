#include "player.h"

Player::Player(QString& name, QColor& color)
    : name_(name), money_(0), color_(color)
{
}

Player::Player(QString& name, QColor& color, int money)
    : name_(name), money_(money), color_(color)
{
}

QString Player::getName() { return name_; }

Region* Player::getRegion(int index) { return regions_[index]; }

QColor Player::getColor() { return color_; }

int Player::countRegions() { return regions_.size(); }

bool Player::isLess(const Player& rhs) const { return name_ < rhs.name_; }

void Player::addRegion(Region* region, bool flag)
{
    // getting the region and setting to it player's color
    regions_.push_back(region);
    if (!flag) region->setBrush(color_);
    // filling the characteristics of the region
    region->setFree(false);
    region->setOwned(true);
    region->setOwner(name_);
}

void Player::addCity(City& city) { cities_.push_back(city); }

bool operator<(const Player& lhs, const Player& rhs) { return lhs.isLess(rhs); }
