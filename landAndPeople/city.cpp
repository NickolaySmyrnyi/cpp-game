#include "city.h"

City::City() {}

City::City(QString owner) : owner_(owner) {}

void City::setName(QString name) { name_ = name; }

void City::setRegion(QString name) { region_ = name; }

void City::setOwner(QString name) { owner_ = name; }

void City::setCapital(bool flag) { capital_ = flag; }

QString City::getOwner() { return owner_; }

QString City::getName() { return name_; }
