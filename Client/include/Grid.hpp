#pragma once
#include <vector>
#include <stdfloat>

class Grid{
    public:
        Grid();

        void fillValueGrid();

    private:
        std::vector<std::vector<std::float32_t>> m_valueGrid;
};