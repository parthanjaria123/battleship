#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

const int grid_width = 500, margin = 100;
const int window_width = 2 * grid_width + 3 * margin, window_height = grid_width + 2 * margin;

Vector2f cellSize(grid_width / 10, grid_width / 10);

RenderWindow window(VideoMode(window_width, window_height), "Battleship");
RectangleShape grid[10][10];

void show_battleship(int board_type, int x_coordinate, int y_coordinate,int orientation, int length)
{
    /*@ param
    board_type: 0 if the first board, 1 if the second board
    x_coordinate/y_coordinate: includes index 0 ; the value of the unit cell to start on the grid
    orientation: how to orient the ship 1) north, 2) east, 3) south, 4) west
    length: how long the ship is*/

    ConvexShape convex;
    convex.setPointCount(5);

    int ini_x_point = margin+grid_width/10*x_coordinate;
    int ini_y_point = margin+grid_width/10*y_coordinate;

    //NOTE: NEED TO EDIT ORIENTATION 1, 2, and 4

    if(orientation==1)
    {
        convex.setPoint(0,Vector2f(ini_x_point+(margin+grid_width)*board_type, ini_y_point));
        convex.setPoint(1,Vector2f(ini_x_point+(margin+grid_width)*board_type+grid_width/10-5.0, ini_y_point));
        convex.setPoint(2,Vector2f(ini_x_point+(margin+grid_width)*board_type+grid_width/10-5.0, ini_y_point+grid_width/10*length-grid_width/20-5));
        convex.setPoint(3,Vector2f((ini_x_point+(margin+grid_width)*board_type+grid_width/10+ini_x_point+(margin+grid_width)*board_type)/2, ini_y_point+grid_width/10*length-5));
        convex.setPoint(4,Vector2f(ini_x_point+(margin+grid_width)*board_type, ini_y_point+grid_width/10*length-grid_width/20-5));
    }
    if(orientation==2)
    {
        convex.setPoint(0,Vector2f(ini_x_point+(margin+grid_width)*board_type, ini_y_point));
        convex.setPoint(1,Vector2f(ini_x_point+(margin+grid_width)*board_type+grid_width/10-5.0, ini_y_point));
        convex.setPoint(2,Vector2f(ini_x_point+(margin+grid_width)*board_type+grid_width/10-5.0, ini_y_point+grid_width/10*length-grid_width/20-5));
        convex.setPoint(3,Vector2f((ini_x_point+(margin+grid_width)*board_type+grid_width/10+ini_x_point+(margin+grid_width)*board_type)/2, ini_y_point+grid_width/10*length-5));
        convex.setPoint(4,Vector2f(ini_x_point+(margin+grid_width)*board_type, ini_y_point+grid_width/10*length-grid_width/20-5));
    }
    if(orientation==3)
    {
        convex.setPoint(0,Vector2f(ini_x_point+(margin+grid_width)*board_type, ini_y_point));
        convex.setPoint(1,Vector2f(ini_x_point+(margin+grid_width)*board_type+grid_width/10-5.0, ini_y_point));
        convex.setPoint(2,Vector2f(ini_x_point+(margin+grid_width)*board_type+grid_width/10-5.0, ini_y_point+grid_width/10*length-grid_width/20-5));
        convex.setPoint(3,Vector2f((ini_x_point+(margin+grid_width)*board_type+grid_width/10+ini_x_point+(margin+grid_width)*board_type)/2, ini_y_point+grid_width/10*length-5));
        convex.setPoint(4,Vector2f(ini_x_point+(margin+grid_width)*board_type, ini_y_point+grid_width/10*length-grid_width/20-5));
    }
    if(orientation==4)
    {
        convex.setPoint(0,Vector2f(ini_x_point+(margin+grid_width)*board_type, ini_y_point));
        convex.setPoint(1,Vector2f(ini_x_point+(margin+grid_width)*board_type+grid_width/10-5.0, ini_y_point));
        convex.setPoint(2,Vector2f(ini_x_point+(margin+grid_width)*board_type+grid_width/10-5.0, ini_y_point+grid_width/10*length-grid_width/20-5));
        convex.setPoint(3,Vector2f((ini_x_point+(margin+grid_width)*board_type+grid_width/10+ini_x_point+(margin+grid_width)*board_type)/2, ini_y_point+grid_width/10*length-5));
        convex.setPoint(4,Vector2f(ini_x_point+(margin+grid_width)*board_type, ini_y_point+grid_width/10*length-grid_width/20-5));
    }

    convex.setFillColor(Color::Green);

    window.draw(convex);
}

void draw_gridlines(float x, float y, RectangleShape g[10][10])
{
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            g[i][j].setSize(cellSize);
            g[i][j].setOutlineColor(Color::Black);
            g[i][j].setOutlineThickness(5.0f);

            g[i][j].setPosition(i*cellSize.x + x, j*cellSize.y + y);

            window.draw(g[i][j]);
        }
    }
}

/*
status is 0: player turn, or 1:opponent turn
*/
void display_turn(int status)
{
    string turn;
    if(status)
        turn = "Not Your Turn";
    else
        turn = "Your Turn";

    Font font;
    if(!font.loadFromFile("Lato-Medium.ttf"))
        return;
    Text text(turn, font, 50);
    text.setPosition(window_width / 2 - text.getLocalBounds().width / 2, margin / 2 - text.getLocalBounds().height / 2);
    window.draw(text);
}

void show_grid()
{
    while(window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        display_turn(1);

        draw_gridlines(margin, margin, grid);
        draw_gridlines(grid_width + 2 * margin, margin, grid);

        show_battleship(0,6,6,3,3);
        show_battleship(0,4,4,3,2);

        window.display();
        window.clear(Color::Blue);
    }

}

int main()
{
    show_grid();
}

