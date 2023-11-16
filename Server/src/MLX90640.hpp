#pragma once

#include <Wire.h>
#include <Adafruit_MLX90640.h>

namespace MLX90640{
    const int SDA_PIN = 4;
    const int SCL_PIN = 5;

    const uint8_t MLX90640_ADDR = 0x33;

    const uint8_t MLX90640_PIXEL_WIDTH = 32;
    const uint8_t MLX90640_PIXEL_HEIGHT = 24;

    class MLX90640{
        public:
            MLX90640();

            bool begin(const int sda = SDA_PIN,
                        const int scl = SCL_PIN,
                        const uint8_t addr = MLX90640_ADDR,
                        const mlx90640_mode_t mode = MLX90640_CHESS,
                        const mlx90640_resolution_t resolution = MLX90640_ADC_18BIT,
                        const mlx90640_refreshrate_t refreshRate = MLX90640_2_HZ);

        private:
            TwoWire m_i2c;
            Adafruit_MLX90640 m_mlx90640;
    };
}