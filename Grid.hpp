#ifndef GRID_HPP_INCLUDED
#define GRID_HPP_INCLUDED

#include <cinttypes>
#include <vector>
#include <ctime>
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

    Segment (uint8_t x_in, uint8_t y_in)
    {
        x = x_in;
        y = y_in;
    }

    Segment (uint8_t x_in, uint8_t y_in, Direction next_in)
    {
        x = x_in;
        y = y_in;

        next = next_in;
    }

    Segment () {}

    bool operator == (const Segment &temp) const
    {
        return ((x == temp.x) && (y == temp.y));
    }

    friend class Grid;
};

class Grid : public sf::Drawable
{
    const uint8_t GRID_GAP    = 1;
    const uint8_t CELL_SIZE   = 20;
    const sf::Color bodyColor = sf::Color::Yellow;
    const sf::Color headColor = sf::Color::Red;
    const int8_t offX [4]     = {0, 1, 0, -1};
    const int8_t offY [4]     = {-1, 0, 1, 0};

    bool            alive;
    uint8_t         gridWidth, gridHeight;
    //std::vector     <std::vector <sf::Color>> cellColor; // I might not need cellColor
    std::vector     <Segment> snake;
    std::vector     <Segment> fruit;
    sf::VertexArray vertArray;
    uint32_t        score = 0;
    uint16_t        speed = 8; // 8 blocks per second

    bool    addSegment; //
    Segment newSegment; // Used by updateSnake

    virtual void draw (sf::RenderTarget&, sf::RenderStates) const;
    void         reset();
    bool         testForCollision() const;
    void         addFruit();
    bool         fruitOn (Segment seg) const;
    bool         fruitOnRemove (Segment seg);

public:

    Grid     (uint8_t gridWidth, uint8_t gridHeight);
    void     updateSnake();
    void     updateVertexArray();
    uint32_t getScore() const;
    bool     isAlive() const;
    void     inputKey (char);
    void     terminate();
};

#endif // GRID_HPP_INCLUDED
