#include <SFML/Graphics.hpp>
#include <iostream>
#include <queue>
#include <utility>
#include <string>
#include <vector>

#include "battleship.h"

using namespace sf;
using namespace std;

const int graphics_grid_width = 500, margin = 100;
const int window_width = 2 * graphics_grid_width + 3 * margin, window_height = graphics_grid_width + 2 * margin;

Vector2f cellSize(graphics_grid_width / 10, graphics_grid_width / 10);
Color sea(0, 191, 255);
Color light_sea(0, 191, 255, 170);
Color gray(105, 105, 105);
string winlabel;

Sprite sprite;
int status = 2;
int sizes[5] = {5, 4, 3, 3, 2};
string names[5] = {"Aircraft Carrier", "Battleship", "Submarine", "Cruiser", "Destroyer"};
pair<int, int> point1 = make_pair(-1,-1), point2 = make_pair(-1,-1);
grid p1;
grid p2;

bool prevbit = false, clickstate = false;

RenderWindow window(VideoMode(window_width, window_height), "Battleship");
RectangleShape graphics_grid[10][10];
RectangleShape battle_grid[10][10];

queue<pair<int, int> > lit_cells;

int sgn(int x)
{
    if(x == 0)
        return 0;
    else if(x > 0)
        return 1;
    else
        return -1;
}

void show_battleship(battleship* bs)
{
    // int px = bs->pos.x * cellSize.x + margin, py = bs->pos.y * cellSize.y + margin;

    // ConvexShape convex;
    // convex.setPointCount(5);
    // convex.setPoint(0,Vector2f(px, py));
    // convex.setPoint(1,Vector2f(px + bs->length * cellSize.x - 5, py));
    // convex.setPoint(2,Vector2f(px + bs->length * cellSize.x - 5, py + cellSize.y - 5));
    // convex.setPoint(3,Vector2f(px, py + cellSize.y - 5));

    // convex.setFillColor(Color(0, 0, 0));

    // window.draw(convex);

    for(int i = 0; i < bs->length; i++)
    {
        int nx = bs->pos.x + i * bs->dir.x;
        int ny = bs->pos.y + i * bs->dir.y;

        graphics_grid[nx][ny].setFillColor(Color::Black);
    }
}

void draw_graphics_gridlines(float x, float y, RectangleShape g[10][10])
{
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            g[i][j].setSize(cellSize);
            g[i][j].setOutlineColor(Color::Black);
            g[i][j].setOutlineThickness(5.0f);

            g[i][j].setPosition(i * cellSize.x + x, j * cellSize.y + y);

            window.draw(g[i][j]);
        }
    }
}

/*
status is 0: player turn, or 1:opponent turn
*/
void display_turn(int stat)
{
    string turn;
    if(stat == 1)
        turn = winlabel;
    else if(stat >= 2)
        turn = "Place Ship: " + names[stat - 2] + " (" + to_string(sizes[stat - 2]) + " units)";
    else
        turn = "Your Turn";

    Font font;
    if(!font.loadFromFile("Lato-Medium.ttf"))
        return;
    Text text(turn, font, 50);
    text.setPosition(window_width / 2 - text.getLocalBounds().width / 2, margin / 2 - text.getLocalBounds().height / 2);
    window.draw(text);
}

void show_graphics_grid()
{
    while(window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        display_turn(status);

        draw_graphics_gridlines(margin, margin, graphics_grid);
        draw_graphics_gridlines(graphics_grid_width + 2 * margin, margin, battle_grid);

        //show_battleship(1,1);

        //Vector2f pos = sprite.getPosition();

        sf::Vector2i pos = sf::Mouse::getPosition(window);
        sprite.setPosition(pos.x, pos.y);
        int grid_X = (pos.x - margin) / cellSize.x;
        int grid_Y = (pos.y - margin) / cellSize.y;

        if(grid_X >= 0 && grid_X < 10 && grid_Y >= 0 && grid_Y < 10)
        {
            while(!lit_cells.empty())
            {
                pair<int, int> lit = lit_cells.front();
                lit_cells.pop();

                if(graphics_grid[lit.first][lit.second].getFillColor() != Color::Black)
                    graphics_grid[lit.first][lit.second].setFillColor(Color::White);
                if(battle_grid[lit.first][lit.second].getFillColor() != Color::Black)
                    battle_grid[lit.first][lit.second].setFillColor(Color::White);
            }

            bool bit = sf::Mouse::isButtonPressed(sf::Mouse::Left);
            if(graphics_grid[grid_X][grid_Y].getFillColor() == Color::White)
            {
                graphics_grid[grid_X][grid_Y].setFillColor(bit ? sea : light_sea);
                lit_cells.push(make_pair(grid_X, grid_Y));
            }

            if(bit)
            {
                if(status >= 2)
                {
                    if((point1.first == -1 && point1.second == -1) && (grid_X != point2.first || grid_Y != point2.second))
                    {
                        point1 = make_pair(grid_X, grid_Y);
                        cout << "point1: " << point1.first << ' ' << point1.second << endl;
                    }
                    else if((point1.first != -1 || point1.second != -1) && (point1.first != grid_X || point1.second != grid_Y))
                    {
                        point2 = make_pair(grid_X, grid_Y);
                        cout << "point2: " << point2.first << ' ' << point2.second << endl;


                        bool valid = true;

                        battleship newship;
                        newship.length = sizes[status - 2];
                        newship.pos.x = point1.first;
                        newship.pos.y = point1.second;
                        newship.dir.x = sgn(point2.first - point1.first);
                        newship.dir.y = sgn(point2.second - point1.second);
                        newship.hits = 0;
                        if(newship.dir.x != 0 && newship.dir.y != 0)
                            valid = false;
                        newship.name = names[status - 2];

                        cout << "dir: " << newship.dir.x << ' ' << newship.dir.y << endl;

                        int farx = point1.first + (newship.length - 1) * newship.dir.x;
                        int fary = point1.second + (newship.length - 1) * newship.dir.y;
                        if(farx < 0 || farx >= 10 || fary < 0 || fary >= 10)
                            valid = false;

                        int cx = point1.first, cy = point1.second;
                        for(int i = 0; i < newship.length && valid; i++)
                        {
                            cx = point1.first + i * newship.dir.x;
                            cy = point1.second + i * newship.dir.y;

                            graphics_grid[cx][cy].setFillColor(Color::Black);
                        }

                        if(valid)
                        {
                            p1.ships[status - 2] = newship;
                            p2.ships[status - 2] = newship;
                            status++;
                            if(status >= 7)
                                status = 0;
                            cout << "yay" << endl;
                        }

                        point1 = make_pair(-1,-1);
                    }
                }
            }
        }

        grid_X = (pos.x - 2 * margin - graphics_grid_width) / cellSize.x;
        if(grid_X >= 0 && grid_X < 10 && grid_Y >= 0 && grid_Y < 10)
        {
            while(!lit_cells.empty())
            {
                pair<int, int> lit = lit_cells.front();
                lit_cells.pop();

                if(battle_grid[lit.first][lit.second].getFillColor() != Color::Black)
                    battle_grid[lit.first][lit.second].setFillColor(Color::White);
                if(graphics_grid[lit.first][lit.second].getFillColor() != Color::Black)
                    graphics_grid[lit.first][lit.second].setFillColor(Color::White);
            }

            bool bit = sf::Mouse::isButtonPressed(sf::Mouse::Left);
            if(battle_grid[grid_X][grid_Y].getFillColor() == Color::White)
            {
                battle_grid[grid_X][grid_Y].setFillColor(bit ? sea : light_sea);
                lit_cells.push(make_pair(grid_X, grid_Y));
            }

            if(bit)
            {
                if(status == 0 && point1 != make_pair(grid_X, grid_Y))
                {
                    vec2d shot;
                    shot.x = grid_X, shot.y = grid_Y;
                    update(&p2, shot);

                    vector<vec2d> cpu_shots;
                    for(int i = 0; i < 10; i++)
                    {
                        for(int j = 0; j < 10; j++)
                        {
                            vec2d cpu_shot;
                            cpu_shot.x = i, cpu_shot.y = j;
                            if(p1.boom.count(cpu_shot) == 0 && p1.miss.count(cpu_shot) == 0)
                                cpu_shots.push_back(cpu_shot);
                        }
                    }

                    vec2d selected = cpu_shots[rand() % cpu_shots.size()];
                    cout << selected.x << ' ' << selected.y << endl;
                    update(&p1, selected);

                    point1 = make_pair(grid_X, grid_Y);

                    int sunk1 = 0, sunk2 = 0;

                    cout << "P1" << endl;
                    for(int i = 0; i < 5; i++)
                    {
                        battleship z = p1.ships[i];
                        cout << z.name << ": " + to_string(z.hits) + "/" + to_string(z.length) << endl;
                        if(z.hits == z.length)
                            sunk1++;
                    }
                    cout << endl;
                    cout << "P2" << endl;;
                    for(int i = 0; i < 5; i++)
                    {
                        battleship z = p2.ships[i];
                        cout << z.name << ": " + to_string(z.hits) + "/" + to_string(z.length) << endl;
                        if(z.hits == z.length)
                            sunk2++;
                    }
                    cout << endl;

                    if(sunk1 == 5)
                    {
                        status = 1;
                        winlabel = "YOU LOST!!!";
                    } else if(sunk2 == 5)
                    {
                        status = 1;
                        winlabel = "YOU WON!!!";
                    }
                }
            }
        }

        set<vec2d>::iterator it;
        for(it = p1.boom.begin(); it != p1.boom.end(); it++)
        {
            vec2d curr = *it;
            graphics_grid[curr.x][curr.y].setFillColor(Color::Red);
        }

        for(it = p1.miss.begin(); it != p1.miss.end(); it++)
        {
            vec2d curr = *it;
            graphics_grid[curr.x][curr.y].setFillColor(gray);
        }

        for(it = p2.boom.begin(); it != p2.boom.end(); it++)
        {
            vec2d curr = *it;
            battle_grid[curr.x][curr.y].setFillColor(Color::Magenta);
        }

        for(it = p2.miss.begin(); it != p2.miss.end(); it++)
        {
            vec2d curr = *it;
            battle_grid[curr.x][curr.y].setFillColor(gray);
        }

        for(it = p2.sunk.begin(); it != p2.sunk.end(); it++)
        {
            vec2d curr = *it;
            battle_grid[curr.x][curr.y].setFillColor(Color::Green);
        }

        window.draw(sprite);

        window.display();
        window.clear(Color::Blue);
    }

}

int main()
{
    Image cur;
    if (!cur.loadFromFile("cursor.png"))
        return -1;

    Texture texture;
    texture.loadFromImage(cur);  //Load Texture from image
    sprite.setTexture(texture);
    sprite.scale(0.3, 0.3);

    show_graphics_grid();
    cout<<"this point is being passed"<<endl;
}
