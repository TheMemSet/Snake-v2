#include "Grid.hpp"

int main()
{
    sf::RenderWindow window (sf::VideoMode (1280, 720), "Temporary title");
    window.setFramerateLimit (30);

    sf::Event ev;

    while (window.isOpen ())
    {
        while (window.pollEvent (ev))
        {
            if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
                window.close ();
            if (ev.type == sf::Event::Closed)
                window.close ();
        }

        window.clear ();
        window.display ();
    }
    return 0;
}
