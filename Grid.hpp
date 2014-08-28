#ifndef GRID_HPP_INCLUDED
#define GRID_HPP_INCLUDED

#include <cinttypes>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <SFML/Graphics.hpp>

enum Direction
{
    up = 0,
    right,
    down,
    left
};

class Segment
{
    uint8_t x, uint8_t y;
    Direction dir;

    Segment (uint8_t x_in, uint8_t y_in, Direction dir_in)
    {
        x = x_in;
        y = y_in;

        dir = dir_in;
    }

    Segment () {}

    friend class Grid;
};

class Grid : public sf::Drawable
{
    const uint8_t GRID_GAP = 1;
    bool alive;
    uint8_t gridWidth, gridHeight;
    std::vector <std::vector <sf::Color>> cellColor;
    std::vector <Segment> segment;

    virtual void draw (sf::RenderTarget&, sf::RenderStates) const;

public:

    Grid     (uint8_t gridWidth_in, uint8_t gridHeight_in);
    void     updateSnake();
    uint32_t getScore();
    bool     isAlive();
    void     inputKey (sf::Keyboard);
    void     terminate();
};

#endif // GRID_HPP_INCLUDED
