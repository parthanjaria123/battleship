#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

const int grid_width = 500, margin = 100;
const int window_width = 2 * grid_width + 3 * margin, window_height = grid_width + 2 * margin;

Vector2f cellSize(grid_width / 10, grid_width / 10);

RenderWindow window(VideoMode(window_width, window_height), "Battleship");
RectangleShape grid[10][10];

void show_battleship(/*int x_coordinate, int y_coordinate*/)
{
    ConvexShape convex;
    convex.setPointCount(5);
    convex.setPoint(0,Vector2f(100.f,100.f));
    convex.setPoint(1,Vector2f(400.f,100.f));
    convex.setPoint(2,Vector2f(400.f,700.f));
    convex.setPoint(3,Vector2f(250.f,850.f));
    convex.setPoint(4,Vector2f(100.f,700.f));

    convex.setFillColor(Color::White);

    window.draw(convex);
}

void draw_gridlines(float x, float y)
{

    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            grid[i][j].setSize(cellSize);
            grid[i][j].setOutlineColor(Color::Black);
            grid[i][j].setOutlineThickness(5.0f);

            grid[i][j].setPosition(i*cellSize.x + x, j*cellSize.y + y);

            window.draw(grid[i][j]);
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

        draw_gridlines(margin, margin);
        draw_gridlines(grid_width + 2 * margin, margin);

        //show_battleship();

        window.display();
        window.clear(Color::Blue);
    }

}

int main()
{
    show_grid();
    cout<<"this point is being passed"<<endl;
}
