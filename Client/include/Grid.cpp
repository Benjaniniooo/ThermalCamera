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

    void Grid::copyDataFromRawBuffer(const std::uint8_t* data, const size_t size){
        for(size_t i = 0; i < size; i++){
            int x = (int) (i / m_size.width);
            int y = i % m_size.height;

            //copy four bytes of data from the buffer to the valueGrid at (x,y) and bitcast it to a std::float32_t
            std::memcpy(&m_valueGrid.at(x).at(y), &data[i * 4], sizeof(std::float32_t));
        }
    }
}