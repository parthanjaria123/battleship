#ifndef BATTLESHIP_H_INCLUDED
#define BATTLESHIP_H_INCLUDED

#include <string>
#include <set>

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

    std::string name; // ship name
};

struct grid
{
    battleship ships[5]; // contains all ships on grid

    std::set<vec2d> boom; // contains opponent's successful shots
    std::set<vec2d> miss; // contains opponent's unsuccessful shots
    std::set<vec2d> sunk; // contains positions of sunken ship segments
};

bool between(int a, int b, int c);
bool shot_landed(battleship* ship, vec2d shot);
char analyze_spot(grid* g, vec2d spot);
void update(grid* g, grid* g2, vec2d shot);

#endif // BATTLESHIP_H_INCLUDED
