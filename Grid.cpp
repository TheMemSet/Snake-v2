#include "Grid.hpp"
#include <cstdlib>

Grid::Grid (uint8_t gridWidth_in, uint8_t gridHeight_in) : alive (true)
{
    gridHeight = gridHeight_in;
    gridWidth  = gridWidth_in;

    vertArray.setPrimitiveType (sf::Quads);

    reset();
}

void Grid::draw (sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw (vertArray, states);
}

uint32_t Grid::getScore() const
{
    return score;
}

void Grid::terminate()
{
    alive = false;
}

bool Grid::isAlive() const
{
    return alive;
}

void Grid::reset()
{
    /*
    cellColor.resize (gridWidth);

    for (uint16_t i = 0;i < gridWidth;++i)
    {
        cellColor [i].resize (gridHeight);

        for (uint16_t j = 0;j < gridHeight;++j)
        {
            cellColor [i] [j] = sf::Color::Black;
        }
    }
    */ // I might not need cellColor

    snake.clear();

    for (uint8_t i = 0;i < 5;++i)
    {
        snake.push_back (Segment (4 - i, 0, right));
    }
}

void Grid::updateSnake()
{
    snake [0].x += offX [snake [0].next];
    snake [0].y += offY [snake [0].next];

    if (fruitOnRemove (snake [snake.size() - 1]))
    {
        addSegment = true;
        newSegment = snake [snake.size() - 1];
    }
    else
    {
        addSegment = false;
    }


    for (uint16_t i = 1;i < snake.size();++i)
    {
        snake [i].x += offX [snake [i].next];
        snake [i].y += offY [snake [i].next];
    }

    for (uint16_t i = snake.size() - 1;i > 0;++i)
    {
        snake [i].next = snake [i + 1].next;
    }

    if (addSegment)
    {
        snake.push_back (newSegment);
    }

    if (fruitOn (snake [0]))
    {
        score += speed;
        addFruit();
    }

    alive = !testForCollision();
}

bool Grid::testForCollision() const
{
    if ((snake [0].x < 0) || (snake [0].x >= gridWidth) || (snake [0].y < 0) || (snake [0].y >= gridHeight))
    {
        return true;
    }

    for (uint16_t i = 1;i < snake.size();++i)
    {
        if (snake [i] == snake [0])
        {
            return true;
        }
    }

    return false;
}

void Grid::updateVertexArray()
{
    vertArray.clear();

    for (uint16_t i = 0;i < fruit.size();++i)
    {
        fruit [i].x *= CELL_SIZE;
        fruit [i].y *= CELL_SIZE;

        vertArray.append (sf::Vertex (sf::Vector2f (fruit [i].x, fruit [i].y),
        sf::Color::Green));

        vertArray.append (sf::Vertex (sf::Vector2f (fruit [i].x + (CELL_SIZE - GRID_GAP), fruit [i].y),
        sf::Color::Green));

        vertArray.append (sf::Vertex (sf::Vector2f (fruit [i].x + (CELL_SIZE - GRID_GAP), fruit [i].y + (CELL_SIZE - GRID_GAP)),
        sf::Color::Green));

        vertArray.append (sf::Vertex (sf::Vector2f (fruit [i].x, fruit [i].y + (CELL_SIZE - GRID_GAP)),
        sf::Color::Green));

        fruit [i].x /= CELL_SIZE;
        fruit [i].y /= CELL_SIZE;
    }

    for (uint16_t i = 0;i < snake.size();++i)
    {
        snake [i].x *= CELL_SIZE;
        snake [i].y *= CELL_SIZE;

        vertArray.append (sf::Vertex (sf::Vector2f (snake [i].x, snake [i].y),
        (!i) ? sf::Color::Red : sf::Color::Yellow));

        vertArray.append (sf::Vertex (sf::Vector2f (snake [i].x + (CELL_SIZE - GRID_GAP), snake [i].y),
        (!i) ? sf::Color::Red : sf::Color::Yellow));

        vertArray.append (sf::Vertex (sf::Vector2f (snake [i].x + (CELL_SIZE - GRID_GAP), snake [i].y + (CELL_SIZE - GRID_GAP)),
        (!i) ? sf::Color::Red : sf::Color::Yellow));

        vertArray.append (sf::Vertex (sf::Vector2f (snake [i].x, snake [i].y),
        (!i) ? sf::Color::Red : sf::Color::Yellow));

        snake [i].x /= CELL_SIZE;
        snake [i].y /= CELL_SIZE;
    }
}

bool Grid::fruitOn (Segment seg) const
{
    for (uint16_t i = 0;i < fruit.size();++i)
    {
        if (fruit [i] == seg) return true;
    }

    return false;
}

bool Grid::fruitOnRemove (Segment seg)
{
    for (uint16_t i = 0;i < fruit.size();++i)
    {
        if (fruit [i] == seg)
        {
            fruit.erase (fruit.begin() + i);
            return true;
        }
    }

    return false;
}

void Grid::inputKey (char key)
{
    switch (key)
    {
    case 'U':
        if (snake [0].next != down)
        {
            snake [0].next = up;
        }
        break;

    case 'R':
        if (snake [0].next != left)
        {
            snake [0].next = right;
        }
        break;

    case 'D':
        if (snake [0].next != up)
        {
            snake [0].next = down;
        }
        break;

    case 'L':
        if (snake [0].next != right)
        {
            snake [0].next = left;
        }
        break;

    case 'S': // As in, "Start over"
        reset();
        break;

    case 'A': // As in, "Accelerate"
        speed++;
        break;

    case 'E': // As in, "Exit"
        alive = false;
        break;

    default:
        exit (1001);
    }
}
