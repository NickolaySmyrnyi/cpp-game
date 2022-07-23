#include "game.h"

Game::Game(QWidget* parent) : QGraphicsView(parent)
{
    // creating the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 1300, 900);
    setScene(scene);
    setFixedSize(1300, 900);
    setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);

    // creating and visualizing the field
    field_ = new Field();
    scene->addItem(field_);

    // crating players by user
    int countries = QInputDialog::getInt(
        this, tr("Starting"), tr("Input the number of countries"), 4, 2, 8, 1);
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

    // adding button
    button = new QPushButton(this);
    button->setGeometry(50, 750, 200, 100);
    button->setText("Show the landscape");
    scene->addWidget(button);

    // connecting changing of text
    // connecting adding names to regions and cities
    // connectimg message about starting of the game
    // connecting adding message about new event
    connect(field_, &Field::signal1, panel_, &Events::changeText);
    connect(field_, &Field::signal2, this, &Game::addNames);
    connect(field_, &Field::signal3, panel_, &Events::startGame);
    connect(field_, &Field::signal4, panel_, &Events::messageAdded);
    connect(button, &QPushButton::clicked, this, &Game::showLandscape);

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
    int numberOfActions = rand() % 3 + 3;
    while (numberOfActions != 0)
    {
        int action = rand() % 3;
        switch (action)
        {
            case 0:
                betterRelation();
                break;
            case 1:
                worseRelation();
                break;
        }
        --numberOfActions;
    }
}

void Game::betterRelation()
{
    int player1 = rand() % field_->countPlayers();
    int player2 = rand() % field_->countPlayers();
    if (player1 == player2) return;
    int result = field_->changeRelations(player1, player2, 5);
    if (result == 0)
    {
        panel_->messageAdded(field_->getPlayer(player1).getName() + " and " +
                             field_->getPlayer(player2).getName() +
                             "\nstarted relationships");
        return;
    }
    else
    {
        panel_->messageAdded(field_->getPlayer(player1).getName() + " and " +
                             field_->getPlayer(player2).getName() +
                             "\nare looking forward \nto a better relations");
        if (result == 1)
        {
            panel_->messageAdded(
                field_->getPlayer(player1).getName() + " and " +
                field_->getPlayer(player2).getName() + "\nbecome friends");
            return;
        }
        if (result == 4)
        {
            panel_->messageAdded(field_->getPlayer(player1).getName() +
                                 " and " +
                                 field_->getPlayer(player2).getName() +
                                 "\nstopped being enemies");
            return;
        }
    }
}

void Game::worseRelation()
{
    int player1 = rand() % field_->countPlayers();
    int player2 = rand() % field_->countPlayers();
    if (player1 == player2) return;

    int result = field_->changeRelations(player1, player2, -4);
    if (result == 0)
    {
        panel_->messageAdded(field_->getPlayer(player1).getName() + " and " +
                             field_->getPlayer(player2).getName() +
                             "\nstarted relationships");
        return;
    }
    else
    {
        panel_->messageAdded(field_->getPlayer(player1).getName() + " and " +
                             field_->getPlayer(player2).getName() +
                             "\nare worried about relations");
        if (result == 2)
        {
            panel_->messageAdded(field_->getPlayer(player1).getName() +
                                 " and " +
                                 field_->getPlayer(player2).getName() +
                                 "\nstopped being friends");
            return;
        }
        if (result == 3)
        {
            panel_->messageAdded(
                field_->getPlayer(player1).getName() + " and " +
                field_->getPlayer(player2).getName() + "\nbecome enemies");
            return;
        }
    }
}

void Game::addNames(City& city, Region* region, bool flag)
{
    // gray brush in order for user to see the region
    region->setBrush(Qt::gray);

    QString regionName = QInputDialog::getText(
        this, QString(city.getOwner()), QString("Input the name of the region"),
        QLineEdit::Normal, "Region");
    region->setName(regionName);
    if (flag)
    {
        QString cityName = QInputDialog::getText(
            this, QString(city.getOwner()),
            QString("Input the name of the city"), QLineEdit::Normal, "City");
        city.setName(cityName);
        city.setRegion(regionName);
    }
    if (field_->isLandscape()) region->setLandscapeColor();
}

void Game::showLandscape()
{
    if (field_->isLandscape())
    {
        field_->becomePolitical();
        button->setText("Show the landscape map");
    }
    else
    {
        field_->becomeLandscape();
        button->setText("Show the political map");
    }
    setFocus();
}
