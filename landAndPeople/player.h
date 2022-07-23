#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <QVector>

#include "region.h"

class Player
{
   public:
    // constructors
    Player(QString& name, QColor& color);
    Player(QString& name, QColor& color, int money);

    void addRegion(Region* region, bool flag);

    // setters
    void addCity(City& city);

    // getters
    QString getName();
    Region* getRegion(int index);
    QColor getColor();

    // number of player's regions
    int countRegions();

    // communication with other players
    QMap<Player, int> countries;

    // operators
    bool isLess(const Player& rhs) const;

   private:
    // name, color and amount of money of a player
    QString name_;
    QColor color_;
    int money_;

    // all player's regions and cities
    QVector<Region*> regions_;
    QVector<City> cities_;
};

bool operator<(const Player& lhs, const Player& rhs);

#endif  // PLAYER_H
