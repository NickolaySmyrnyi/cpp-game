#ifndef CITY_H
#define CITY_H

#include <QString>
#include <QVector>

class City
{
   public:
    // constructors
    City();

   private:
    // names of city , its region and its country
    QString name;
    QString region;
    QString owner;

    // list of buildings in the city
    QVector<QString> buildings;

    // number of money from city
    int money;
};

#endif  // CITY_H
