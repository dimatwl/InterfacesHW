#include "game.h"

Game::Game()
{
    QPoint pt(0,0);
    this->addItem(new Ball(10, pt));
}
