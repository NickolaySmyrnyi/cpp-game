#ifndef CITY_H
#define CITY_H

#include <QString>
#include <QVector>

class City
{
   public:
    // constructors
    City();
    City(QString player);

    // setters
    void setName(QString name);
    void setRegion(QString name);
    void setOwner(QString name);
    void setCapital(bool flag);

    // getters
    QString getOwner();

   private:
    // names of city , its region and its country
    QString name_;
    QString region_;
    QString owner_;

    // showing is city a capital
    bool capital_ = false;

    // list of buildings in the city
    QVector<QString> buildings_;

    // number of money from city
    int money_ = 0;
};

#endif  // CITY_H
