#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

const sf::Color start_color = sf::Color::Green;
const sf::Color end_color = sf::Color::Red;

class Cell{
    public:
        sf::RectangleShape cell_property;
    public:
        enum Type{
            START,
            END
        };
    public:
        Cell();
        Cell(sf::Vector2f size, sf::Vector2f position);
        int column, row;
        sf::Color state;
        Type type;
    
    public:
        sf::Vector2f size;


    public:
        void update();
        void render(sf::RenderTarget* target);
    
    public:
        void setColor();
};
