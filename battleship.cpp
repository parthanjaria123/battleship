#include <iostream>
#include <set>
using namespace std;

struct vec2d
{
    int x, y;

    bool operator<(const vec2d &a) const
    {
        return (x < a.x || y < a.y);
    }
};

struct battleship
{
    vec2d pos; // position of the head of the ship
    vec2d dir; // ship orientation
    int length; // ship size
    int hits; // number of times the ship has been struck

    string name; // ship name
};

struct grid
{
    battleship ships[5]; // contains all ships on grid

    set<vec2d> boom; // contains successful shots
    set<vec2d> miss; // contains unsuccessful shots
    set<vec2d> sunk; // contains positions of sunken ship segments
};

bool between(int a, int b, int c)
{
    int new_b = min(b, c), new_c = max(b, c);
    return a >= new_b && a <= new_c;
}

bool shot_landed(battleship* ship, vec2d shot)
{
    if(ship->dir.x == 0 && ship->pos.x == shot.x)
        return between(shot.y, ship->pos.y, ship->pos.y + (ship->length - 1) * ship->dir.y);

    if(ship->dir.y == 0 && ship->pos.y == shot.x)
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

void update(grid* g, vec2d shot)
{
    bool miss = true;
    for(int i = 0; i < 5; i++)
    {
        if(g->ships[i].hits != g->ships[i].length && g->boom.count(shot) == 0 && shot_landed(&(g->ships[i]), shot))
        {
            miss = false;
            g->ships[i].hits++;
            cout << g->ships[i].hits << endl;
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

int main()
{
    // -------------------------------- testing code --------------------------------

    grid grid1;
    grid grid2;

    grid1.ships[0].pos.x = 0;
    grid1.ships[0].pos.y = 0;
    grid1.ships[0].dir.x = 0;
    grid1.ships[0].dir.y = 1;
    grid1.ships[0].length = 2;
    grid1.ships[0].hits = 0;
    grid1.ships[0].name = "prth";

    grid2 = grid1;
    grid2.ships[0].name = "prth2";

    vec2d shot;
    shot.x = shot.y = 0;
    update(&grid1, shot);

    shot.y = 1;
    update(&grid1, shot);

    shot.y = 2;
    update(&grid1, shot);

    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            vec2d spot;
            spot.x = i;
            spot.y = j;
            cout << analyze_spot(&grid1, spot);
        }
        cout << endl;
    }

    // ----------------------------- end tester code --------------------------------
    return 0;
}
