#include "../../include/interface/Engine.h"

//defining initializer functions
void Engine::initVariables(){
    this->window = nullptr;

    //loading the font
    try{
        this->font.loadFromFile("../fonts/dejavu-sans/ttf/DejaVuSans.ttf");
    }catch(...){
        std::cout << "Couldn't load the font" << std::endl;
    }

    //default values for start and end cell
    this->startCell.column = this->startCell.row = -1;
    this->endCell.column = this->endCell.row = -1;
}
void Engine::initWindow(){
    this->video_mode.width = 600;
    this->video_mode.height = 600;
    this->window = new sf::RenderWindow(this->video_mode, "FindPath", sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);
    this->window->setFramerateLimit(60);
    //variables related with the grid
    this->size = this->video_mode.width/20;
    this->column = 20;
    this->row = 20;
    //calling grid layout function
    this->configureGridLayout(this->column, this->row);
}

//defining constructor and destructor
Engine::Engine(){
    this->initVariables();
    this->initWindow();
}
Engine::~Engine(){
    delete this->window;
}

//defining accessors
const bool Engine::running() const{
    return this->window->isOpen();
}

//defining window functions
void Engine::pollEvent(){
    while(this->window->pollEvent(this->event)){
        switch(this->event.type){
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::MouseButtonPressed:
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    this->pointLocation(this->mouse_position_view);
                    if((this->startCell.column != -1 && this->startCell.row != -1) && (this->endCell.column != -1 && this->endCell.row != -1))
                        this->dijkstra.findPath(startCell, endCell, this->grid_vector);
                break;
            case sf::Event::MouseWheelScrolled:
                if(this->event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel){
                    if(this->event.mouseWheelScroll.delta > 0)
                        if(this->cell_type < 2)
                            this->cell_type++;
                        else
                            this->cell_type = 0;
                    else if(this->event.mouseWheelScroll.delta < 0)
                        if(this->cell_type > 0)
                            this->cell_type--;
                        else
                            this->cell_type = 2;
                }
                break;
        }
    }
}
void Engine::update(){
    this->pollEvent();
    this->mouse_position = sf::Mouse::getPosition(*this->window);
    this->mouse_position_view = this->window->mapPixelToCoords(this->mouse_position);

    std::string cell_type_string = this->cell_type == 0 ? "Start Point" : 
    this->cell_type == 1 ? "End Point" : 
    "Block";

    this->setText(cell_type_string);

    for(int i = 0; i < this->grid_vector.size(); i++){
        for(int j = 0; j < this->grid_vector[i].size(); j++){
            this->grid_vector[i][j].update();
        }
    }
}
void Engine::render(){
    this->window->clear(sf::Color::Black);

    for(int i = 0; i < this->grid_vector.size(); i++){
        for(int j = 0; j < this->grid_vector[i].size(); j++){
            grid_vector[i][j].render(this->window);
        }
    }

    this->window->draw(this->text);

    this->window->display();
}

//defining custom functions
void Engine::configureGridLayout(int column, int row){
    for(int i = 0; i < this->row; i++){
        std::vector<Cell> vec_in;
        for(int j = 0; j < this->column; j++){
            Cell cell = Cell(sf::Vector2f(this->size, this->size), sf::Vector2f(j * this->size, i * this->size));
            cell.column = j;
            cell.row = i;
            vec_in.push_back(cell);
        }
        this->grid_vector.push_back(vec_in);
    }
}
void Engine::pointLocation(sf::Vector2f mouse_position){
    int mouse_row = floor(mouse_position.y/this->size);
    int mouse_column = floor(mouse_position.x/this->size);

    this->grid_vector[mouse_row][mouse_column].type = this->cell_type == 0 ? 
    Cell().START: this->cell_type == 1 ? Cell().END : Cell().BLOCK;

    //saving start and end cell for use in another function..
    if(this->cell_type == 0)
        this->startCell = this->grid_vector[mouse_row][mouse_column];
    else if(this->cell_type == 1)
        this->endCell = this->grid_vector[mouse_row][mouse_column];

    //revert cell state and remove cell from previously selected container
    for(int i = this->selected_cells.size()-1; i >= 0; i--){
        if(this->grid_vector[this->selected_cells[i].row][this->selected_cells[i].column].type == this->grid_vector[mouse_row][mouse_column].type){
            this->grid_vector[this->selected_cells[i].row][this->selected_cells[i].column].type = Cell().EMPTY;
            this->selected_cells.erase(this->selected_cells.begin() + i);
        }
    }

    //store selected cell if only it's start and end cell
    this->prev_row = mouse_row;
    this->prev_column = mouse_column;
    if(this->grid_vector[this->prev_row][this->prev_column].type != Cell().BLOCK)
        this->selected_cells.push_back(this->grid_vector[this->prev_row][this->prev_column]);
} 

void Engine::setText(std::string particle_text){
    this->text.setFont(this->font);
    this->text.setString(particle_text);
    this->text.setCharacterSize(18);
    this->text.setFillColor(sf::Color::White);
    this->text.setPosition(sf::Vector2f(this->video_mode.width/1.2f, this->video_mode.height/1.1f));
}