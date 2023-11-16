////////////////////////////////////////////////////////////
/// \file AMG88xx.hpp
/// \author Benjaniniooo (39649250+Benjaniniooo@users.noreply.github.com)
/// \brief Library that serves as an interface to the AMG88xx
/// \version 0.1
/// \date 2023-11-14
/// 
/// @copyright Copyright (c) 2023
/// 
////////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Wire.h>
#include <Adafruit_AMG88xx.h>


namespace AMG88xx{
    const int SDA_PIN = 4;
    const int SCL_PIN = 5;

    const uint8_t AMG88xx_ADDR = 0x69;

    const uint8_t AMG88xx_PIXEL_WIDTH = 8;
    const uint8_t AMG88xx_PIXEL_HEIGHT = 8;


    ////////////////////////////////////////////////////////////
    /// \brief Wrapper for the AMG88xx chip and it's I2C interface
    /// 
    ////////////////////////////////////////////////////////////
    class AMG88xx{
        public:
            ////////////////////////////////////////////////////////////
            /// \brief Default constructor
            ///
            /// This constructor does not initialize the AMG88xx, nor 
            /// does it start the interface; use begin() to do so.  
            ///
            ////////////////////////////////////////////////////////////
            AMG88xx();
            
            ////////////////////////////////////////////////////////////
            /// \brief Start the I2C interface to the AMG88xx and boot up the chip
            /// 
            /// \param sda      SDA pin to use for the I2C interface
            /// \param scl      SCL pin to use for the I2C interface
            /// \param addr     address of the AMG88xx on the I2C bus
            /// \return true    if the initialization of the AMG88xx was successful
            ///
            ////////////////////////////////////////////////////////////
            bool begin( const int sda = SDA_PIN, 
                        const int scl = SCL_PIN, 
                        const uint8_t addr = AMG88xx_ADDR);

            ////////////////////////////////////////////////////////////
            /// \brief Read the pixels from the AMG88xx chip and store it to an array
            /// 
            /// You can poll pixels from the AMG88xx with a refresh rate
            /// of 10 Hz maximum. 
            /// 
            ////////////////////////////////////////////////////////////
            void pollPixels();

            float m_pixels[AMG88xx_PIXEL_ARRAY_SIZE];
            
        private:
            ////////////////////////////////////////////////////////////
            // Member data
            ////////////////////////////////////////////////////////////
            TwoWire m_i2c;
            Adafruit_AMG88xx m_amg8833;
    };
} // namespace AMG88xx
