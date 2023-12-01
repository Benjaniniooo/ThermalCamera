#pragma once

#include <stdfloat>
#include <cstdint>
#include <cstring>


#include <vector>
#include <array>

#include <iostream>

namespace Grid
{
    typedef struct{
        unsigned int width;
        unsigned int height;
    } ARRAY_SIZE;
    
    const ARRAY_SIZE AMG8833_ARRAY_SIZE = {8, 8};
    const ARRAY_SIZE MLX90640_ARRAY_SIZE = {32, 24};
    const ARRAY_SIZE MOCK_SERVER_ARRAY_SIZE = {16, 16};

    class Grid{
        public:
            Grid();

            void create(const unsigned int width, const unsigned int height);
            void create(const ARRAY_SIZE size);

            void copyDataFromRawBuffer(const std::uint8_t* buffer, const size_t size);

        private:
            std::vector<std::vector<std::float32_t>> m_valueGrid;
            ARRAY_SIZE m_size;
    };
}