#include "MLX90640.hpp"

namespace MLX90640{
    MLX90640::MLX90640()
        : m_i2c(TwoWire(0))
        , m_MLX90640(Adafruit_MLX90640()){}

    bool MLX90640::begin(const int sda, const int scl, const uint8_t addr, const mlx90640_mode_t mode, const mlx90640_resolution_t resolution, const mlx90640_refreshrate_t refreshRate){
        m_i2c.begin(sda, scl);
        
        if(!m_mlx90640.begin(addr, &m_i2c)){
            log_e("MLX90640 did not connect via I2C!");
            return false;
        }

        m_mlx90640.setMode(mode);
        m_mlx90640.setResolution(resolution);
        m_mlx90640.setRefreshRate(refreshRate);

        return true;
    }
}