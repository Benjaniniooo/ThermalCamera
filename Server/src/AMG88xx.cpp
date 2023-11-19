#include "AMG88xx.hpp"

namespace AMG88xx{
    AMG88xx::AMG88xx()
        : m_i2c(TwoWire(0))
        , m_amg8833(Adafruit_AMG88xx()){}

    bool AMG88xx::begin(const int sda, const int scl, const uint8_t addr){
        m_i2c.begin(sda, scl);

        if(!m_amg8833.begin(addr, &m_i2c)){
            return false;
        }

        return true;
    }

    void AMG88xx::pollPixels(){
        m_amg8833.readPixels(m_pixels);
    }
}