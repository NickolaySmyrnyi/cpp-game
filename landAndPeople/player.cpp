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

int Player::countRegions() { return regions_.size(); }

void Player::addRegion(Region* region)
{
    // getting the region and setting to it player's color
    regions_.push_back(region);
    region->setBrush(color_);
    // filling the characteristics of the region
    region->setFree(false);
    region->setOwned(true);
    region->setOwner(name_);
}

void Player::addCity(City& city) { cities_.push_back(city); }
