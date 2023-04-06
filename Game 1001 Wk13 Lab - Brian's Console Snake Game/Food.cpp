#include "Food.h"

void Food::placeFood(Snake snake)
{
    bool safe = true;

    do {
        safe = true;
        position.x = (rand() % (WIDTH - 2)) + 1;
        position.y = (rand() % (HEIGHT - 2)) + 3;
        for (const Pos s : snake.getBody())
            if (position == s)
                safe = false;
    } while (!safe);

}

Pos Food::getPos()
{
    return position;
}
