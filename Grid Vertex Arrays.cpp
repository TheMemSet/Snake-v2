#include "Grid.hpp"

void Grid::updateVertexArray()
{
    if (!alive)
    {
        return;
    }

    vertArray.clear();



    uint16_t last = fruit.size() - 1;

    fruit [last].x *= CELL_SIZE;
    fruit [last].y *= CELL_SIZE;

    vertArray.append (sf::Vertex (sf::Vector2f (fruit [last].x, fruit [last].y), sf::Vector2f (bodyTextureX, bodyTextureY)));

    vertArray.append (sf::Vertex (sf::Vector2f (fruit [last].x + CELL_SIZE, fruit [last].y), sf::Vector2f (bodyTextureX + TEXTURE_SIZE, bodyTextureY)));

    vertArray.append (sf::Vertex (sf::Vector2f (fruit [last].x + CELL_SIZE, fruit [last].y + CELL_SIZE), sf::Vector2f (bodyTextureX + TEXTURE_SIZE,
    bodyTextureY + TEXTURE_SIZE)));

    vertArray.append (sf::Vertex (sf::Vector2f (fruit [last].x, fruit [last].y + CELL_SIZE), sf::Vector2f (bodyTextureX, bodyTextureY + TEXTURE_SIZE)));

    fruit [last].x /= CELL_SIZE;
    fruit [last].y /= CELL_SIZE;


    /*for (uint16_t i = 0;i < snake.size();++i)
    {
        snake [i].x *= CELL_SIZE;
        snake [i].y *= CELL_SIZE;

        vertArray.append (sf::Vertex (sf::Vector2f (snake [i].x, snake [i].y),
        (!i) ? headColor : bodyColor));

        vertArray.append (sf::Vertex (sf::Vector2f (snake [i].x + (CELL_SIZE - GRID_GAP), snake [i].y),
        (!i) ? headColor : bodyColor));

        vertArray.append (sf::Vertex (sf::Vector2f (snake [i].x + (CELL_SIZE - GRID_GAP), snake [i].y + (CELL_SIZE - GRID_GAP)),
        (!i) ? headColor : bodyColor));

        vertArray.append (sf::Vertex (sf::Vector2f (snake [i].x, snake [i].y + (CELL_SIZE - GRID_GAP)),
        (!i) ? headColor : bodyColor));

        snake [i].x /= CELL_SIZE;
        snake [i].y /= CELL_SIZE;
    }*/

    Direction nextOfLast;

    for (int16_t i = snake.size() - 1;i >= 0;--i) // i should be unsigned, but then the break condition is never met
    {
        snake [i].x *= CELL_SIZE;
        snake [i].y *= CELL_SIZE;

        if (i == (snake.size() - 1))
        {
            //std::cout << 1;
            vertArray.append (sf::Vertex (sf::Vector2f (snake [i].x, snake [i].y), sf::Vector2f (tailTextureX, tailTextureY)));

            vertArray.append (sf::Vertex (sf::Vector2f (snake [i].x + CELL_SIZE, snake [i].y), sf::Vector2f (tailTextureX + TEXTURE_SIZE, tailTextureY)));

            vertArray.append (sf::Vertex (sf::Vector2f (snake [i].x + CELL_SIZE, snake [i].y + CELL_SIZE), sf::Vector2f (tailTextureX + TEXTURE_SIZE,
            tailTextureY + TEXTURE_SIZE)));

            vertArray.append (sf::Vertex (sf::Vector2f (snake [i].x, snake [i].y + CELL_SIZE), sf::Vector2f (tailTextureX, tailTextureY + TEXTURE_SIZE)));

            rotateSegment (vertArray.getVertexCount() - 4, snake [i].next);

            nextOfLast = snake [i].next;
            //std::cout << 2;
        }
        else if (!i)
        {
            vertArray.append (sf::Vertex (sf::Vector2f (snake [i].x, snake [i].y), sf::Vector2f (headTextureX, headTextureY)));

            vertArray.append (sf::Vertex (sf::Vector2f (snake [i].x + CELL_SIZE, snake [i].y), sf::Vector2f (headTextureX + TEXTURE_SIZE, headTextureY)));

            vertArray.append (sf::Vertex (sf::Vector2f (snake [i].x + CELL_SIZE, snake [i].y + CELL_SIZE), sf::Vector2f (headTextureX + TEXTURE_SIZE,
            headTextureY + TEXTURE_SIZE)));

            vertArray.append (sf::Vertex (sf::Vector2f (snake [i].x, snake [i].y + CELL_SIZE), sf::Vector2f (headTextureX, headTextureY + TEXTURE_SIZE)));

            rotateSegment (vertArray.getVertexCount() - 4, snake [i].next);
        }
        else
        {

            //if (nextOfLast == snake [i].next)
            {
                vertArray.append (sf::Vertex (sf::Vector2f (snake [i].x, snake [i].y), sf::Vector2f (bodyTextureX, bodyTextureY)));
                //std::cout << 1;

                vertArray.append (sf::Vertex (sf::Vector2f (snake [i].x + CELL_SIZE, snake [i].y), sf::Vector2f (bodyTextureX + TEXTURE_SIZE, bodyTextureY)));
                //std::cout << 2;

                vertArray.append (sf::Vertex (sf::Vector2f (snake [i].x + CELL_SIZE, snake [i].y + CELL_SIZE), sf::Vector2f (bodyTextureX + TEXTURE_SIZE,
                bodyTextureY + TEXTURE_SIZE)));
                //std::cout << 3;

                vertArray.append (sf::Vertex (sf::Vector2f (snake [i].x, snake [i].y + CELL_SIZE), sf::Vector2f (bodyTextureX, bodyTextureY + TEXTURE_SIZE)));
                //std::cout << 4;

                rotateSegment (vertArray.getVertexCount() - 4, snake [i].next);
                //std::cout << 5;

                nextOfLast = snake [i].next;
                //std::cout << 6;
            }
        }

        snake [i].x /= CELL_SIZE;
        snake [i].y /= CELL_SIZE;

        //std::cout << i;
    }
}
