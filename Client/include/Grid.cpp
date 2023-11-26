#include "Grid.hpp"

namespace Grid{
    Grid::Grid(){
    }

    void Grid::create(const unsigned int width, const unsigned int height){
        m_valueGrid.resize(width, std::vector<std::float32_t>(height, 0.f));
        
        m_size.width = width;
        m_size.height = height;
    }

    void Grid::create(const ARRAY_SIZE size){
        m_valueGrid.resize(size.width, std::vector<std::float32_t>(size.height, 0.f));

        m_size = size;
    }
}