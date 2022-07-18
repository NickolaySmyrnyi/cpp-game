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
    field = new Field();
    scene->addItem(field);

    // crating players by user
    int countries =
        QInputDialog::getInt(this, tr("Number of countries"),
                             tr("Input the number of countries"), 4, 2, 8, 1);
    for (size_t i = 0; i < countries; ++i)
    {
        QString name = QInputDialog::getText(
            this, QString("Country " + QString::number(i + 1)),
            QString("Input the name"), QLineEdit::Normal, "Name");
        Player* tempPlayer = new Player(name, colors[i]);
        field->addPlayer(tempPlayer);
    }

    // making field visible
    field->appear();

    // adding panel with events
    panel = new Events();
    panel->changeText(field->getPlayer(0)->getName());
    scene->addItem(panel);

    // connecting changing of text
    // connectingadding names
    connect(field, &Field::signal1, panel, &Events::changeText);
    connect(field, &Field::signal2, this, &Game::addNames);
    connect(field, &Field::signal3, panel, &Events::startGame);

    // showing the game
    show();
}

void Game::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Space)
    {
        panel->printYears();
        makeAction();
    }
}

void Game::makeAction()
{
    if (!field->isNotFree()) field->findNewRegion();
}

void Game::addNames(Region* region, bool flag)
{
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
