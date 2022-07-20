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

   private:
    // name, color and amount of money of a player
    QString name_;
    QColor color_;
    int money_;

    // communication with other players
    QVector<QMap<Player, int>> friends_;
    QVector<QMap<Player, int>> enemies_;
    QVector<QMap<Player, int>> neutral_;

    // all player's regions and cities
    QVector<Region*> regions_;
    QVector<City> cities_;
};

#endif  // PLAYER_H
