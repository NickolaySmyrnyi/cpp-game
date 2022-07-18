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

    // setters
    void addRegion(Region* region);

    // getters
    QString getName();
    Region* getRegion(int index);

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

    // all player's regions
    QVector<Region*> regions_;
};

#endif  // PLAYER_H
