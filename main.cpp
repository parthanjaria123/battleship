#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

RenderWindow window(VideoMode(1000, 1000), "Battleship");
RectangleShape grid[10][10];


void show_battleship(/*int x_coordinate, int y_coordinate*/)
{
    ConvexShape convex;
    convex.setPointCount(5);
    convex.setPoint(0,Vector2f(200.f,100.f));
    convex.setPoint(1,Vector2f(300.f,100.f));
    convex.setPoint(2,Vector2f(300.f,300.f));
    convex.setPoint(3,Vector2f(250.f,400.f));
    convex.setPoint(4,Vector2f(200.f,300.f));

    convex.setFillColor(Color::Red);

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.draw(convex);
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

        Vector2f cellSize(100.f, 100.f);

        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++){
                grid[i][j].setSize(cellSize);
                grid[i][j].setOutlineColor(Color::Black);
                grid[i][j].setOutlineThickness(5.0f);

                grid[i][j].setPosition(i*cellSize.x + 1.0f, j*cellSize.y + 1.0f);

                window.draw(grid[i][j]);

            }
        }

        show_battleship();
        window.display();
    }

}

int main()
{
    show_grid();
    cout<<"this point is being passed"<<endl;
}
