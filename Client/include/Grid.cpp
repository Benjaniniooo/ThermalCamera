#include "Grid.hpp"

namespace Grid{
    Grid::Grid(){

    }

    void Grid::create(const unsigned int x_size, const unsigned int y_size){
        m_valueGrid.resize(x_size, std::vector<std::float32_t>(y_size, 0.f));
        
        m_size.width = x_size;
        m_size.height = y_size;
    }

    void Grid::create(const ARRAY_SIZE size){
        m_valueGrid.resize(size.width, std::vector<std::float32_t>(size.height, 0.f));

        m_size = size;
    }
}