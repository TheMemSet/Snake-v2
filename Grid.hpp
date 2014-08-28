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
    uint8_t x, y;
    Direction next;

    Segment (uint8_t x_in, uint8_t y_in, Direction next_in)
    {
        x = x_in;
        y = y_in;

        next = next_in;
    }

    Segment () {}

    friend class Grid;
};

class Grid : public sf::Drawable
{
    const uint8_t GRID_GAP    = 1;
    const uint8_t CELL_SIZE   = 20;
    const sf::Color bodyColor = sf::Color::Yellow;
    const sf::Color headColor = sf::Color::Red;

    bool alive;
    uint8_t gridWidth, gridHeight;
    std::vector <std::vector <sf::Color>> cellColor;
    std::vector <Segment> snake;
    sf::VertexArray vertArray;
    uint32_t score = 0;
    uint16_t speed = 8; // 8 blocks per second

    virtual void draw (sf::RenderTarget&, sf::RenderStates) const;

public:

    Grid     (uint8_t gridWidth, uint8_t gridHeight);
    void     updateSnake();
    void     updateVertexArray();
    uint32_t getScore() const;
    bool     isAlive() const;
    void     inputKey (sf::Keyboard);
    void     terminate();
};

#endif // GRID_HPP_INCLUDED
