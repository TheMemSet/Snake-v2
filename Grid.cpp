#include "Grid.hpp"
#include <cstdlib>

Grid::Grid (uint8_t gridWidth_in, uint8_t gridHeight_in) : alive (true)
{
    if (!(textureAtlas.loadFromFile ("Resources/Atlas.png")))
    {
        exit (1004);
    }

    gridHeight = gridHeight_in;
    gridWidth  = gridWidth_in;

    vertArray.setPrimitiveType (sf::Quads);

    srand (time (NULL));

    reset();
}

void Grid::draw (sf::RenderTarget& target, sf::RenderStates states) const
{
    states.texture = &textureAtlas;
    target.draw (vertArray, states);
}

std::string Grid::getScore() const
{
    return scoreString;
}

bool Grid::isAlive() const
{
    return alive;
}

void Grid::updateScoreString()
{
    scoreString.clear();
    uint32_t score_copy = score;

    do
    {
        scoreString += (score_copy % 10) + '0';
        score_copy /= 10;
    } while (score_copy > 0);

    std::reverse (scoreString.begin(), scoreString.end());
}

void Grid::reset()
{
    snake.clear();
    fruit.clear();
    alive = true;
    score = 0;
    scoreString = "0";
    speed = defaultSpeed;

    for (uint8_t i = 0;i < 5;++i)
    {
        snake.push_back (Segment ((gridWidth / 2) - i, gridHeight / 2, right));
    }

    addFruit();
}

void Grid::updateSnake()
{
    if (!alive)
    {
        return;
    }

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

    for (uint16_t i = snake.size() - 1;i > 0;--i)
    {
        snake [i].next = snake [i - 1].next;
    }

    if (addSegment)
    {
        snake.push_back (newSegment);
    }

    if (fruitOn (snake [0]))
    {
        score += speed;
        updateScoreString();
        addFruit();
    }

    alive = !testForCollision();

    updateVertexArray();
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
            if (!(snake [1].y < snake [0].y))
            {
                snake [0].next = up;
            }
        }
        break;

    case 'R':
        if (snake [0].next != left)
        {
            if (!(snake [1].x > snake [0].x))
            {
                snake [0].next = right;
            }
        }
        break;

    case 'D':
        if (snake [0].next != up)
        {
            if (!(snake [1].y > snake [0].y))
            {
                snake [0].next = down;
            }
        }
        break;

    case 'L':
        if (snake [0].next != right)
        {
            if (!(snake [1].x < snake [0].x))
            {
                snake [0].next = left;
            }
        }
        break;

    case 'S': // As in, "Start over"
        reset();
        break;

    case 'A': // As in, "Accelerate"
        speed += 2;
        break;

    default:
        exit (1001);
    }
}

uint16_t Grid::getSpeed() const
{
    return speed;
}

void Grid::addFruit()
{
    if (((gridHeight * gridWidth) - snake.size() - 1) <= 0)
    {
        return;
    }

    uint32_t nextFruitCell = (rand() % ((gridHeight * gridWidth) - snake.size())) + 1;

    for (uint16_t xx = 0;xx < gridWidth;++xx)
    {
        for (uint16_t yy = 0;yy < gridHeight;++yy)
        {
            if (!(fruitOn (Segment (xx, yy)) || snakeOn (Segment (xx, yy))))
            {
                nextFruitCell--;

                if (!nextFruitCell)
                {
                    fruit.push_back (Segment (xx, yy));
                    return;
                }
            }
        }
    }
}

bool Grid::snakeOn (Segment seg) const
{
    for (uint32_t i = 0;i < snake.size();++i)
    {
        if (snake [i] == seg) return true;
    }

    return false;
}

bool Grid::isTerminated() const
{
    return terminated;
}

void Grid::terminate()
{
    terminated = true;
}

void Grid::rotateSegment (uint16_t firstVertex, uint16_t nRot)
{
    //std::cout << firstVertex << " " << snake.size() << '\n';
    if (nRot > 3)
    {
        exit (1003);
    }

    else
    {
        sf::Vertex tempVertex;

        for (uint8_t i = 0;i < nRot;++i)
        {
            tempVertex = vertArray [firstVertex + 3];
            vertArray [firstVertex + 3] = vertArray [firstVertex + 2];
            vertArray [firstVertex + 2] = vertArray [firstVertex + 1];
            vertArray [firstVertex + 1] = vertArray [firstVertex];
            vertArray [firstVertex] = tempVertex;
        }
    }
}
