#include <set>
using namespace std;

struct vec2d
{
    int x, y;
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