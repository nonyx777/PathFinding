#include "../../../include/dijkstra/Dijkstra.hpp"

//defining constructor
Dijkstra::Dijkstra(){
    //...
}

//defining functions
void Dijkstra::setupNeighbours(std::vector<std::vector<Cell>>& grid_vector){
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 20; j++){
            if((j > 0 && i > 0) && (j < 19 && i < 19)){
                //top
                grid_vector[i-1][j-1].type = Cell().VISITED;
                grid_vector[i-1][j].type = Cell().VISITED;
                grid_vector[i-1][j+1].type = Cell().VISITED;
                //middle
                grid_vector[i][j-1].type = Cell().VISITED;
                grid_vector[i][j+1].type = Cell().VISITED;
                //botto
                grid_vector[i+1][j-1].type = Cell().VISITED;
                grid_vector[i+1][j].type = Cell().VISITED;
                grid_vector[i+1][j+1].type = Cell().VISITED;
            }
        }
    }
}