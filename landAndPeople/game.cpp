#include "game.h"

Game::Game(QWidget* parent) : QGraphicsView(parent)
{
    // creating the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 1300, 800);
    setScene(scene);
    setFixedSize(1300, 800);
    setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);

    // creating and visualizing the field
    field_ = new Field();
    scene->addItem(field_);

    // crating players by user
    int countries =
        QInputDialog::getInt(this, tr("Number of countries"),
                             tr("Input the number of countries"), 4, 2, 8, 1);
    for (size_t i = 0; i < countries; ++i)
    {
        QString name = QInputDialog::getText(
            this, QString("Country " + QString::number(i + 1)),
            QString("Input the name"), QLineEdit::Normal, "Name");
        Player tempPlayer(name, colors_[i]);
        field_->addPlayer(tempPlayer);
    }

    // making field visible
    field_->appear();

    // adding panel with events
    panel_ = new Events();
    panel_->changeText(field_->getPlayer(0).getName());
    scene->addItem(panel_);

    // connecting changing of text
    // connecting adding names to regions and cities
    // connectimg message about starting of the game
    // connecting adding message about new event
    connect(field_, &Field::signal1, panel_, &Events::changeText);
    connect(field_, &Field::signal2, this, &Game::addNames);
    connect(field_, &Field::signal3, panel_, &Events::startGame);
    connect(field_, &Field::signal4, panel_, &Events::messageAdded);

    // showing the game
    show();
}

// making actions after pressing space
void Game::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Space and panel_->isGameStarted())
    {
        panel_->printYears();
        makeAction();
    }
}

void Game::makeAction()
{
    // spreading regions until it is possible
    if (!field_->isNotFree()) field_->findNewRegion();
}

void Game::addNames(Region* region, bool flag)
{
    // gray brush in order for user to see the region
    region->setBrush(Qt::gray);

    QString regionName = QInputDialog::getText(this, QString("Region"),
                                               QString("Input the name"),
                                               QLineEdit::Normal, "Region");
    region->setName(regionName);
    if (flag)
    {
        QString cityName = QInputDialog::getText(this, QString("City"),
                                                 QString("Input the name"),
                                                 QLineEdit::Normal, "City");
        region->setName(cityName);
    }
}
