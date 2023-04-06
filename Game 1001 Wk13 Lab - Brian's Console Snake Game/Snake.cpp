#include "Snake.h"
#include <iostream>

Snake::Snake(Pos p, int vel)
{
    this->position = p;
    this->speed = vel;

    direction = n;
    length = 1;

    body.push_back(position);
}


Direction Snake::getDirection()
{
    return direction;
}

void Snake::addLength()
{
    length++;
}

Pos Snake::getPos()
{
    return position;
}

std::vector<Pos> Snake::getBody()
{
    return body;
}


void Snake::setDirection(Direction d)
{
    direction = d;
}


void Snake::move()
{
    switch (direction)
    {
    case e:
        position.x += speed;
        break;
    case s:
        position.y += speed;
        break;
    case w:
        position.x -= speed;
        break;
    case n:
        position.y -= speed;
        break;
    }

    body.push_back(position);
    if (body.size() > length)
        body.erase(body.begin());
}

bool snakeHitsWall(Pos p)
{
    if (p.x < 1 || (p.x > (WIDTH - 2)) || (p.y < 3) || (p.y > HEIGHT))
        return true;
    else
        return false;
}

bool Snake::hasCollided()
{
    // Snake head hits body
    for (int i = body.size(); i > 1; i--)
    {
        if (position == body[i - 2])
            return true;
    }

    if (snakeHitsWall(position))
        return true;
    else
        return false;
}

bool Snake::hasFood(Pos foodPos)
{
    if (position == foodPos)
        return true;
    else
        return false;
}

