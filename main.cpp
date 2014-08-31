#include "Grid.hpp"
#include <cstdio>

void updateFunc (Grid*);
void inputFunc (Grid*);

int main()
{
    sf::RenderWindow window (sf::VideoMode (1280, 720), "SnAAAAAke");
    window.setFramerateLimit (60);

    sf::Event ev;

    sf::Font font;
    sf::Text text;

    if (!(font.loadFromFile ("Resources/cambria.ttc")))
    {
        return 1002;
    }

    text.setFont (font);

    Grid grid (64, 36);

    sf::Thread updateThread (&updateFunc, &grid);
    sf::Thread inputThread (&inputFunc, &grid);

    updateThread.launch();
    inputThread.launch();

    while (window.isOpen ())
    {
        while (window.pollEvent (ev))
        {
            if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
                window.close ();
            else if (ev.type == sf::Event::Closed)
                window.close ();
        }

        window.clear   (sf::Color (120, 120, 120));
        window.draw    (grid);
        text.setString ("Score: " + grid.getScore());
        window.draw    (text);

        window.display();
    }

    grid.terminate();
    updateThread.wait();
    inputThread.wait();
    return 0;
}

void updateFunc (Grid *grid)
{
    sf::Clock clock;
    sf::Time elapsedTime, goalTime;

    while (true)
    {
        clock.restart();

        if (grid->isTerminated())
        {
            break;
        }

        goalTime = sf::milliseconds (1000 / grid->getSpeed());

        if (grid->isAlive())
        {
            grid->updateSnake();
        }

        elapsedTime = clock.restart();

        if (goalTime > elapsedTime)
        {
            sf::sleep (goalTime - elapsedTime);
        }
    }
}

void inputFunc (Grid *grid)
{
    sf::Clock clock;
    sf::Time elapsedTime;
    const sf::Time goalTime = sf::milliseconds (10);

    bool isDown [20];

    memset (isDown, 0, sizeof isDown);

    while (true)
    {
        clock.restart();

        if (grid->isTerminated())
        {
            break;
        }

        if (sf::Keyboard::isKeyPressed (sf::Keyboard::Up))
        {
            if (!isDown [0])
            {
                grid->inputKey ('U');
                isDown [0] = true;
            }
        }
        else
        {
            isDown [0] = false;
        }

        if (sf::Keyboard::isKeyPressed (sf::Keyboard::Down))
        {
            if (!isDown [1])
            {
                grid->inputKey ('D');
                isDown [1] = true;
            }
        }
        else
        {
            isDown [1] = false;
        }

        if (sf::Keyboard::isKeyPressed (sf::Keyboard::Left))
        {
            if (!isDown [2])
            {
                grid->inputKey ('L');
                isDown [2] = true;
            }
        }
        else
        {
            isDown [2] = false;
        }

        if (sf::Keyboard::isKeyPressed (sf::Keyboard::Right))
        {
            if (!isDown [3])
            {
                grid->inputKey ('R');
                isDown [3] = true;
            }
        }
        else
        {
            isDown [3] = false;
        }

        if (sf::Keyboard::isKeyPressed (sf::Keyboard::R))
        {
            if (!isDown [4])
            {
                grid->inputKey ('S');
                isDown [4] = true;
            }
        }
        else
        {
            isDown [4] = false;
        }

        if (sf::Keyboard::isKeyPressed (sf::Keyboard::Add))
        {
            if (!isDown [5])
            {
                grid->inputKey ('A');
                isDown [5] = true;
            }
        }
        else
        {
            isDown [5] = false;
        }

        elapsedTime = clock.restart();

        if (goalTime > elapsedTime)
        {
            sf::sleep (goalTime - elapsedTime);
        }
    }
}
