#include "Grid.hpp"

Grid::Grid (uint8_t gridWidth_in, uint8_t gridHeight_in) : alive (true)
{
    gridHeight = gridHeight_in;
    gridWidth  = gridWidth_in;

    cellColor.resize (gridWidth);

    for (uint16_t i = 0;i < gridWidth;++i)
    {
        cellColor [i].resize (gridHeight);

        for (uint16_t j = 0;j < gridHeight;++j)
        {
            cellColor [i] [j] = sf::Color::Black;
        }
    }

    for (uint8_t i = 0;i < 5;++i)
    {
        snake.push_back (Segment (4 - i, 0, right));
    }
}

void Grid::draw (sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw (vertArray, states);
}

uint32_t Grid::getScore() const
{
    return score;
}
