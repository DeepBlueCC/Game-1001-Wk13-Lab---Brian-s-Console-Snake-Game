#pragma once
#include "Snake.h"

class Food
{
private:
    Pos position;

public:
    void placeFood(Snake);

    Pos getPos();
};