#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

const sf::Color start_color = sf::Color::Green;
const sf::Color end_color = sf::Color::Red;
const sf::Color empty_color = sf::Color::Transparent;

class Cell{
    public:
        sf::RectangleShape cell_property;
    public:
        enum Type{
            START,
            END,
            EMPTY
        };
    public:
        Cell();
        Cell(sf::Vector2f size, sf::Vector2f position);
        int column, row;
        sf::Color state;
        Type type;
        std::vector<Cell> neighbours;
    
    public:
        sf::Vector2f size;


    public:
        void update();
        void render(sf::RenderTarget* target);
    
    public:
        void setColor();
};
