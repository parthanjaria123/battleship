#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(200, 200), "SFML works!");

    ConvexShape convex;
    convex.setPointCount(5);
    convex.setPoint(0,Vector2f(10.f,10.f));
    convex.setPoint(1,Vector2f(40.f,10.f));
    convex.setPoint(2,Vector2f(40.f,70.f));
    convex.setPoint(3,Vector2f(25.f,85.f));
    convex.setPoint(4,Vector2f(10.f,70.f));

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(convex);
        window.display();
    }

    return 0;
}
