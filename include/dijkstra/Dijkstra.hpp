#include <iostream>
#include <vector>
#include "../cell/Cell.hpp"

class Dijkstra{
    public:
        Dijkstra();
    public:
        void setupNeighbours(std::vector<std::vector<Cell>>& grid_vector);
        void findPath(Cell& cell);
};