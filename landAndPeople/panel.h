#ifndef PANEL_H
#define PANEL_H

#include <QGraphicsTextItem>

#include "field.h"

class Events : public QGraphicsTextItem
{
   public:
    // constructors
    Events(QGraphicsItem* parent = 0);

    // getters
    bool isGameStarted();

    // qt tools
    void printYears();

   private:
    bool gameStarted_ = false;
    int year_ = 0;
    QVector<QVector<QString>> years_;
    enum seasons
    {
        WINTER,
        SPRING,
        SUMMER,
        AUTUMN
    };

   public slots:
    // changing text for starting regions procedure
    void changeText(QString name);
    void regionAdded(QString name);
    void startGame();
};

#endif  // PANEL_H
