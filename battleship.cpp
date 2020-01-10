#include "battleship.h"
using namespace std;

struct vec2d;
struct battleship;
struct grid;

bool between(int a, int b, int c)
{
    int new_b = min(b, c), new_c = max(b, c);
    return a >= new_b && a <= new_c;
}

bool shot_landed(battleship* ship, vec2d shot)
{
    if(ship->dir.x == 0 && ship->pos.x == shot.x)
        return between(shot.y, ship->pos.y, ship->pos.y + (ship->length - 1) * ship->dir.y);

    if(ship->dir.y == 0 && ship->pos.y == shot.y)
        return between(shot.x, ship->pos.x, ship->pos.x + (ship->length - 1) * ship->dir.x);

    return false;
}

char analyze_spot(grid* g, vec2d spot)
{
    if(g->sunk.count(spot) > 0)
        return 's';
    else if(g->boom.count(spot) > 0)
        return 'b';
    else if(g->miss.count(spot) > 0)
        return 'm';
    else
        return 'e';
}

void update(grid* g, grid* g2, vec2d shot)
{
    bool miss = true;
    for(int i = 0; i < 5; i++)
    {
        if(g->ships[i].hits != g->ships[i].length && g->boom.count(shot) == 0 && shot_landed(&(g->ships[i]), shot))
        {
            miss = false;
            g->ships[i].hits++;
            g->boom.insert(shot);

            if(g->ships[i].hits == g->ships[i].length)
            {
                for(int j = 0; j < g->ships[i].length; j++)
                {
                    vec2d segment;
                    segment.x = g->ships[i].pos.x + g->ships[i].dir.x * j;
                    segment.y = g->ships[i].pos.y + g->ships[i].dir.y * j;
                    g->sunk.insert(segment);
                }
            }
        }
    }

    if(miss)
        g->miss.insert(shot);
}
