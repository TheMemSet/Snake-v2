#include "Grid.hpp"

void Grid::updateSpriteArray()
{
    if (!alive)
    {
        return;
    }

    spriteArray.clear();

    int8_t last = fruit.size() - 1;

    // Fruit updates start
    fruit [last].x *= CELL_SIZE;
    fruit [last].y *= CELL_SIZE;

    spriteArray.push_back (sf::Sprite (textureAtlas, sf::IntRect (bodyTextureX, bodyTextureY, 64, 64)));
    spriteArray [0].setOrigin (32, 32);
    spriteArray [0].setPosition (fruit [last].x + 10, fruit [last].y + 10);
    spriteArray [0].setScale (20. / 64, 20. / 64);

    fruit [last].x /= CELL_SIZE;
    fruit [last].y /= CELL_SIZE;
    //Fruit updates end

    Direction nextOfLast;

    last = 1;

    for (int16_t i = snake.size() - 1;i >= 0;--i) // i should be unsigned, but then the break condition is never met
    {
        snake [i].x *= CELL_SIZE;
        snake [i].y *= CELL_SIZE;

        if (i == (snake.size() - 1))
        {
            spriteArray.push_back (sf::Sprite (textureAtlas, sf::IntRect (tailTextureX, tailTextureY, 64, 64)));
        }
        else if (!i)
        {
            spriteArray.push_back (sf::Sprite (textureAtlas, sf::IntRect (headTextureX, headTextureY, 64, 64)));
        }
        else
        {
            spriteArray.push_back (sf::Sprite (textureAtlas, sf::IntRect (bodyTextureX, bodyTextureY, 64, 64)));
        }

        spriteArray [last].setOrigin (32, 32);
        spriteArray [last].setPosition (snake [i].x + 10, snake [i].y + 10);
        spriteArray [last].setScale (20. / 64, 20. / 64);
        spriteArray [last].setRotation (90 * snake [i].next);

        last++;

        snake [i].x /= CELL_SIZE;
        snake [i].y /= CELL_SIZE;

        //std::cout << i;
    }
}
