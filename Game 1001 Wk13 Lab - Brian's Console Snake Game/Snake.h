#pragma once
#include <vector>

#define WIDTH 75
#define HEIGHT 25
#define HARD_FACTOR 0.95

class Pos
{
public:
    int x, y;
    // Overloading the == operator
    bool operator==(Pos r)
    {
        if ((this->x == r.x) && (this->y == r.y))
            return true;
        else
            return false;
    }
};

enum Direction { e, s, w, n };

class Snake
{
private:
    int length;
    int speed;
    Pos position;
    Direction direction;

    std::vector<Pos> body;
public:
    Snake(Pos, int);

    std::vector<Pos> getBody();
    Pos getPos();
    Direction getDirection();
    void setDirection(Direction);

    void addLength();
    void move();

    bool hasCollided();
    bool hasFood(Pos);
};