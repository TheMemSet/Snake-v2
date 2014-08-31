#ifndef GRID_HPP_INCLUDED
#define GRID_HPP_INCLUDED

#include <cinttypes>
#include <vector>
#include <ctime>
#include <string>
#include <cstring>
#include <iostream> // For debugging purposes only
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
    uint16_t x, y;
    Direction next;

    Segment (uint16_t x_in, uint16_t y_in)
    {
        x = x_in;
        y = y_in;
    }

    Segment (uint16_t x_in, uint16_t y_in, Direction next_in)
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
    const uint8_t CELL_SIZE    = 20;
    const int8_t offX [4]      = {0, 1, 0, -1};
    const int8_t offY [4]      = {-1, 0, 1, 0};
    const uint8_t defaultSpeed = 10;

    const uint16_t headTextureX   = 128, headTextureY   = 64;
    const uint16_t bodyTextureX   =  64, bodyTextureY   = 64;
    const uint16_t tailTextureX   =   0, tailTextureY   =  0;
    const uint16_t cornerTextureX =   0, cornerTextureY = 64;

    sf::Texture     textureAtlas;
    sf::Sprite      headSprite;
    sf::Sprite      bodySprite;
    sf::Sprite      tailSprite;
    sf::Sprite      cornerSprite;
    sf::Sprite      fruitSprite; // Currently using body texture coordinates
    sf::Sprite      backgroundSprite; // Unimplemented

    bool            terminated = false; // Only used for exiting the program
    bool            alive;
    uint8_t         gridWidth, gridHeight;
    std::vector     <Segment> snake;
    std::vector     <Segment> fruit;
    std::vector     <sf::Sprite>  spriteArray;
    uint32_t        score = 0;
    std::string     scoreString = "0";
    uint16_t        speed = defaultSpeed;

    bool       addSegment; //
    Segment    newSegment; // Used by updateSnake
    //sf::Sprite newSprite; // Used by updateVertexArray


    // Functions begin here:
    virtual void draw (sf::RenderTarget&, sf::RenderStates) const;
    void         reset();
    bool         testForCollision() const;
    void         addFruit();
    bool         fruitOn (Segment seg) const;
    bool         fruitOnRemove (Segment seg);
    bool         snakeOn (Segment seg) const;
    void         updateScoreString();
    void         updateSpriteArray();

public:

    Grid        (uint8_t gridWidth, uint8_t gridHeight);
    void        updateSnake();
    std::string getScore() const;
    bool        isAlive() const;
    void        inputKey (char);
    uint16_t    getSpeed() const;
    bool        isTerminated() const;
    void        terminate();
};

#endif // GRID_HPP_INCLUDED
