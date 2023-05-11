#include "../../include/cell/Cell.hpp"

//defining constructors
Cell::Cell(){
    //...
}

Cell::Cell(sf::Vector2f size, sf::Vector2f position){
    this->size = size;

    //forming the shape and related properties
    this->cell_property.setFillColor(sf::Color::Transparent);
    this->cell_property.setOutlineColor(sf::Color::White);
    this->cell_property.setOutlineThickness(0.5f);
    this->cell_property.setSize(this->size);
    this->cell_property.setPosition(position);

}

//defining functions
void Cell::update(){
    setColor();
}
void Cell::render(sf::RenderTarget* target){
    target->draw(this->cell_property);
}

//defining custom functions
void Cell::setColor(){
    switch(this->type){
        case Type::START:
            this->cell_property.setFillColor(start_color);
            break;
        case Type::END:
            this->cell_property.setFillColor(end_color);
            break;
        case Type::EMPTY:
            this->cell_property.setFillColor(empty_color);
            break;
        case Type::PATH:
            this->cell_property.setFillColor(path_color);
    }
}