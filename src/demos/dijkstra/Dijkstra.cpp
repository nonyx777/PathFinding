#include "../../../include/dijkstra/Dijkstra.hpp"

//defining constructor
Dijkstra::Dijkstra(){
    //...
}

//defining functions
void Dijkstra::setupNeighbours(Cell& cell){
    // for(int i = 0; i < 20; i++){
    //     for(int j = 0; j < 20; j++){
    //         if((j > 0 && i > 0) && (j < 19 && i < 19)){
    //             //top
    //             grid_vector[i-1][j-1].type = Cell().VISITED;
    //             grid_vector[i-1][j].type = Cell().VISITED;
    //             grid_vector[i-1][j+1].type = Cell().VISITED;
    //             //middle
    //             grid_vector[i][j-1].type = Cell().VISITED;
    //             grid_vector[i][j+1].type = Cell().VISITED;
    //             //botto
    //             grid_vector[i+1][j-1].type = Cell().VISITED;
    //             grid_vector[i+1][j].type = Cell().VISITED;
    //             grid_vector[i+1][j+1].type = Cell().VISITED;
    //         }
    //     }
    // }
}

void Dijkstra::findPath(Cell& cell, Cell& endCell, std::vector<std::vector<Cell>>& grid_vector){
    if((cell.column > 0 && cell.row > 0) && (cell.column < 19 && cell.row < 19)){
        this->queue.push(cell);
        cell.visited = true;

        while(this->queue.size() != 0){
            cell = this->queue.front();
            if((cell.column == endCell.column && cell.row == endCell.row)){
                Cell* currentCell = &cell;
                // while(currentCell != NULL){
                //     std::cout << currentCell->row << " " << currentCell->column << std::endl;
                //     grid_vector[currentCell->row][currentCell->column].type = Cell().PATH;
                //     currentCell = currentCell->parent;
                // }
                grid_vector[cell.row][cell.column].type = Cell().PATH;
                int p_r = grid_vector[cell.row][cell.column].parent->row;
                int p_c = grid_vector[cell.row][cell.column].parent->column;
                grid_vector[p_r][p_c].type = Cell().PATH;
            }

            this->queue.pop();

            for(int i = cell.row-1; i <= cell.row+1; i++){
                for(int j = cell.column-1; j <= cell.column+1; j++){
                    if((j > 0 && i > 0) && (j < 19 && i < 19)){
                        if(grid_vector[i][j].visited == false){
                            this->queue.push(grid_vector[i][j]);
                            grid_vector[i][j].parent = &grid_vector[cell.row][cell.column];//assigning parent
                            grid_vector[i][j].visited = true;
                        }
                    }
                }
            }
        }
    }
}