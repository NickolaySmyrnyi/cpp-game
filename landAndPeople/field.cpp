#include "field.h"

Field::Field(QGraphicsItem* parent) : QGraphicsRectItem(parent) {}

void Field::appear()
{
    for (int x = 300; x < 1300; x += 50)
    {
        // vector, representing a column, variables for
        // luck (to make some equal regions in a row)
        bool water = false;
        bool forest = false;
        bool desert = false;
        QVector<Region*> column;

        for (int y = 0; y < 900; y += 50)
        {
            // chance for landscape of regions, regions of a
            // field, flag to fill unfilled regions
            int random = rand() % 30;
            Region* tempRegion = new Region(this);
            bool filled = true;

            // setting regions all over the field
            tempRegion->setPos(x, y);

            // random filling information about regions
            if ((water and random < 10) or (!water and random < 5))
            {
                drawWater(tempRegion);
                tempRegion->setWater(true);
                tempRegion->setFree(false);
                // increasing the number of not free regions
                // as nothing can be built on water
                ++notFreeRegions_;
                water = true;
                filled = false;
            }
            else
                water = false;

            if (random == 10)
            {
                drawMountain(tempRegion);
                tempRegion->setMountain(true);
                filled = false;
            }

            if ((desert and random >= 11 and random < 20) or
                (!desert and random >= 11 and random < 17))
            {
                tempRegion->setDesert(true);
                desert = true;
                filled = false;
            }
            else
                desert = false;

            if ((forest and random >= 20 and random < 30) or
                (!desert and random >= 20 and random < 27))
            {
                tempRegion->setForest(true);
                forest = true;
                filled = false;
            }
            else
                forest = false;

            // all non-filled regions are
            // ground regions by default
            if (filled) tempRegion->setGround(true);

            column.push_back(tempRegion);
            tempRegion->setCoordinates(regionVector_.size(), column.size() - 1);
        }
        regionVector_.push_back(column);
    }

    // connecting double click on region with adding it to the player at start
    for (auto& column : regionVector_)
    {
        for (auto& region : column)
        {
            QObject::connect(region, &Region::signal, this,
                             &Field::setStartingRegions);
        }
    }
}

int Field::countPlayers() { return playerVector_.size(); }

int Field::changeRelations(int index1, int index2, int bonus)
{
    if (!playerVector_[index1].countries.contains(playerVector_[index2]))
    {
        playerVector_[index1].countries[playerVector_[index2]] = 0;
        playerVector_[index2].countries[playerVector_[index1]] = 0;
        qDebug() << playerVector_[index1].getName() << ' '
                 << playerVector_[index2].getName();
        return 0;
    }

    playerVector_[index1].countries[playerVector_[index2]] += bonus;
    playerVector_[index2].countries[playerVector_[index1]] += bonus;
    int temp = playerVector_[index1].countries[playerVector_[index2]];
    qDebug() << playerVector_[index1].getName() << ' '
             << playerVector_[index2].getName() << temp;
    if (temp - bonus < 10 and temp >= 10) return 1;
    if (temp - bonus >= 10 and temp < 10) return 2;
    if (temp - bonus > -10 and temp <= -10) return 3;
    if (temp - bonus <= -10 and temp > -10) return 4;
    return 5;
}

void Field::drawWater(Region* water)
{
    ellipse_ = new QGraphicsEllipseItem(this);
    ellipse_->setRect(water->x(), water->y(), water->rect().width(),
                      water->rect().height());
    ellipse_->setBrush(Qt::blue);
}

void Field::drawMountain(Region* mountain)
{
    QVector<QPointF> points{
        {mountain->x(), mountain->y() + mountain->rect().height()},
        {mountain->x() + mountain->rect().width(),
         mountain->y() + mountain->rect().height()},
        {mountain->x() + mountain->rect().width() / 2, mountain->y()}};
    mount_ = new QGraphicsPolygonItem(QPolygonF(points), this);
    mount_->setBrush(Qt::black);
}

void Field::drawCity(Region* city)
{
    ellipse_ = new QGraphicsEllipseItem(this);
    ellipse_->setRect(city->x() + city->rect().width() / 3,
                      city->y() + city->rect().height() / 3,
                      city->rect().width() / 3, city->rect().height() / 3);
    ellipse_->setBrush(Qt::black);
}

Region* Field::findRegion1(Region* region, bool flag)
{
    int x = region->getCoordinates().first;
    int y = region->getCoordinates().second;

    // checking if the region is not on the side
    if (x != 0)
    {
        if (regionVector_[x - 1][y]->isFree()) return regionVector_[x - 1][y];
    }
    if (y != 0)
    {
        if (regionVector_[x][y - 1]->isFree()) return regionVector_[x][y - 1];
    }
    if (x != regionVector_.size() - 1)
    {
        if (regionVector_[x + 1][y]->isFree()) return regionVector_[x + 1][y];
    }
    if (y != regionVector_[0].size() - 1)
    {
        if (regionVector_[x][y + 1]->isFree()) return regionVector_[x][y + 1];
    }

    // if all of four regions are not free we check other regions
    if (flag) return findRegion2(region, false);

    return nullptr;
}

Region* Field::findRegion2(Region* region, bool flag)
{
    int x = region->getCoordinates().first;
    int y = region->getCoordinates().second;

    // checking if the region is not on the side
    if (x != regionVector_.size() - 1 and y != 0)
    {
        if (regionVector_[x + 1][y - 1]->isFree())
            return regionVector_[x + 1][y - 1];
    }
    if (x != regionVector_.size() - 1 and y != regionVector_[0].size() - 1)
    {
        if (regionVector_[x + 1][y + 1]->isFree())
            return regionVector_[x + 1][y + 1];
    }
    if (x != 0 and y != regionVector_[0].size() - 1)
    {
        if (regionVector_[x - 1][y + 1]->isFree())
            return regionVector_[x - 1][y + 1];
    }
    if (x != 0 and y != 0)
    {
        if (regionVector_[x - 1][y - 1]->isFree())
            return regionVector_[x - 1][y - 1];
    }

    // if all of four regions are not free we check other regions
    if (flag) return findRegion1(region, false);

    return nullptr;
}

void Field::findNewRegion()
{
    for (Player& player : playerVector_)
    {
        // choosing random regions for spreading
        int n = player.countRegions();
        int indexFirstRegion = rand() % n;
        int indexSecondRegion = rand() % n;
        bool oneRegion = false, twoRegion = false;

        // choosing randomly from which part to start spreading
        Region* firstRegion = player.getRegion(indexFirstRegion);
        int mode = rand() % 2;

        if (mode)
        {
            Region* newRegion = findRegion1(firstRegion);
            if (newRegion)
            {
                ++notFreeRegions_;
                oneRegion = true;
                player.addRegion(newRegion, landscape_);
            }
        }
        else
        {
            Region* newRegion = findRegion2(firstRegion);
            if (newRegion)
            {
                ++notFreeRegions_;
                oneRegion = true;
                player.addRegion(newRegion, landscape_);
            }
        }

        // if regions are the same, we do not spread the second time
        if (indexFirstRegion != indexSecondRegion)
        {
            Region* secondRegion = player.getRegion(indexSecondRegion);
            int mode = rand() % 2;
            if (mode)
            {
                Region* newRegion = findRegion1(secondRegion);
                if (newRegion)
                {
                    ++notFreeRegions_;
                    twoRegion = true;
                    player.addRegion(newRegion, landscape_);
                }
            }
            else
            {
                Region* newRegion = findRegion2(secondRegion);
                if (newRegion)
                {
                    ++notFreeRegions_;
                    twoRegion = true;
                    player.addRegion(newRegion, landscape_);
                }
            }
        }

        if (oneRegion and twoRegion)
            emit signal4(player.getName() + " added 2 regions");
        else if (oneRegion or twoRegion)
            emit signal4(player.getName() + " added region");
    }
}

// checking if the number of not free regions is equal to the area of field
bool Field::isNotFree()
{
    return notFreeRegions_ == regionVector_.size() * regionVector_[0].size();
}

void Field::becomeLandscape()
{
    for (auto& column : regionVector_)
    {
        for (auto& region : column) region->setLandscapeColor();
    }
    landscape_ = true;
}

void Field::becomePolitical()
{
    for (auto& country : playerVector_)
    {
        for (int i = 0, n = country.countRegions(); i < n; ++i)
            country.getRegion(i)->setBrush(country.getColor());
    }
    for (auto& column : regionVector_)
    {
        for (auto& region : column)
        {
            if (!(region->isOwned() or region->isWater()))
                region->setBrush(Qt::white);
        }
    }
    landscape_ = false;
}

void Field::addPlayer(Player& player) { playerVector_.push_back(player); }

void Field::setLandscape(bool flag) { landscape_ = flag; }

Player Field::getPlayer(int index) { return playerVector_[index]; }

bool Field::isLandscape() { return landscape_; }

void Field::setStartingRegions(Region* region)
{
    // throwing error box if region is not free
    if (!region->isFree() or region->isMountain())
    {
        message_ = new QMessageBox;
        message_->critical(0, "Error",
                           "The region is not free\nChoose another region");
    }
    else
    {
        // counter to set exatly the number of starting regions
        // equal to the players number
        static int counter = 0;

        if (counter < playerVector_.size())
        {
            City newCity(playerVector_[counter].getName());

            // making city in region a capital
            newCity.setCapital(true);

            // pass a signal to input name of region and name of city
            emit signal2(newCity, region);

            // adding new region to a player
            playerVector_[counter].addRegion(region, landscape_);
            playerVector_[counter].addCity(newCity);

            // region is not free now and city is located in it
            ++notFreeRegions_;
            drawCity(region);
            region->setCity(newCity);

            // pass signal to change the label giving hint to a user
            if (counter + 1 != playerVector_.size())
                emit signal1(playerVector_[counter + 1].getName());
            else
                emit signal3();
        }

        // disconecting this connection when the number of players ended
        // connecting double click with getting information
        if (counter == playerVector_.size() - 1)
        {
            for (auto& column : regionVector_)
            {
                for (auto& region : column)
                {
                    QObject::disconnect(region, &Region::signal, this,
                                        &Field::setStartingRegions);
                    QObject::connect(region, &Region::signal, this,
                                     &Field::getRegionInformation);
                }
            }
        }

        ++counter;
    }
}

void Field::getRegionInformation(Region* region)
{
    message_ = new QMessageBox;
    message_->setText(region->getInfo());
    message_->exec();
}
