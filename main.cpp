#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

const int grid_width = 500, margin = 100;
const int window_width = 2 * grid_width + 3 * margin, window_height = grid_width + 2 * margin;

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
    Vector2f cellSize(50.f, 50.f);

    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            grid[i][j].setSize(cellSize);
            grid[i][j].setOutlineColor(Color::Black);
            grid[i][j].setOutlineThickness(5.0f);

            grid[i][j].setPosition(i*cellSize.x + 1.0f + x, j*cellSize.y + 1.0f + y);

            window.draw(grid[i][j]);
        }
    }
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



        draw_gridlines(margin, margin);
        draw_gridlines(grid_width + 2 * margin, margin);

        //show_battleship();

        window.display();
        window.clear(Color::Cyan);
    }

}

int main()
{
    show_grid();
    cout<<"this point is being passed"<<endl;
}
