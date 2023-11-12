#pragma once

#include <Wire.h>
#include <Adafruit_AMG88xx.h>

namespace AMG88xx{
    const int SDA_PIN = 4;
    const int SCL_PIN = 5;

    const uint8_t AMG88xx_ADDR = 0x69;

    const uint8_t AMG88xx_PIXEL_WIDTH = 8;

    class AMG88xx{
        public:
            AMG88xx();
            
            bool begin(const int sda = SDA_PIN, const int scl = SCL_PIN, const uint8_t addr = AMG88xx_ADDR);

            void pollPixels();

            float getPixel(const size_t x, const size_t y);

            float m_pixels[AMG88xx_PIXEL_ARRAY_SIZE];
        protected:
        private:
            TwoWire m_i2c;
            
            Adafruit_AMG88xx m_amg8833;
    };
}
