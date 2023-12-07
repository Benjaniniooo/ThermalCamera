#include "Grid.hpp"

sf::Color hsv(int hue, float sat, float val){
  hue %= 360;
  while(hue<0) hue += 360;

  if(sat<0.f) sat = 0.f;
  if(sat>1.f) sat = 1.f;

  if(val<0.f) val = 0.f;
  if(val>1.f) val = 1.f;

  int h = hue/60;
  float f = float(hue)/60-h;
  float p = val*(1.f-sat);
  float q = val*(1.f-sat*f);
  float t = val*(1.f-sat*(1-f));

  switch(h)
  {
    default:
    case 0:
    case 6: return sf::Color(val*255, t*255, p*255);
    case 1: return sf::Color(q*255, val*255, p*255);
    case 2: return sf::Color(p*255, val*255, t*255);
    case 3: return sf::Color(p*255, q*255, val*255);
    case 4: return sf::Color(t*255, p*255, val*255);
    case 5: return sf::Color(val*255, p*255, q*255);
  }
}

float lerp(float x1, float x2, float y1, float y2, float v){
    return (v - x1) * (y2 - y1) / (x2 - x1) + y1;
}

namespace Grid{
    Grid::Grid(){
    }

    void Grid::create(const unsigned int width, const unsigned int height){
        m_valueGrid.resize(width, std::vector<std::float32_t>(height, 0.f));
        
        m_size.width = width;
        m_size.height = height;

        m_sizeInterpolated.width = (m_size.width - 1) * interpol + m_size.width;
        m_sizeInterpolated.height = (m_size.height - 1) * interpol + m_size.height;

        m_values.resize(m_sizeInterpolated.width, std::vector<std::float32_t>(m_sizeInterpolated.height, 0.f));
    }

    void Grid::create(const ARRAY_SIZE size){
        create(size.width, size.height);
    }

    void Grid::copyDataFromRawBuffer(const std::uint8_t* data, const size_t size){
        if(size == m_size.width * m_size.height * sizeof(std::float32_t)){
            for(size_t y = 0; y < m_size.height; y++){
                for(size_t x = 0; x < m_size.width; x++){
                    std::memcpy(&m_valueGrid.at(x).at(y), &data[((y * m_size.width) + x) * 4], sizeof(std::float32_t));
                }
            }
        }
    }

    void Grid::interpolate(){
        for(size_t x = 0; x < m_size.width; x++){
            for(size_t y = 0; y < m_size.height; y++){
                size_t x_it = x * (interpol + 1);
                size_t y_it = y * (interpol + 1);

                m_values.at(x_it).at(y_it) = m_valueGrid.at(x).at(y);
            }
        }
        // |
        for(size_t x = 0; x < m_size.width; x++){
            for(size_t y = 0; y < m_size.height - 1; y++){
                for(size_t i = 0; i < interpol; i++){
                    std::float32_t temp1 = m_valueGrid.at(x).at(y);
                    std::float32_t temp2 = m_valueGrid.at(x).at(y + 1);
                    std::float32_t diff = (std::float32_t) (i + 1) / (interpol + 1);

                    size_t x_it = x * (interpol + 1);
                    size_t y_it = y * (interpol + 1) + (i + 1);
                    m_values.at(x_it).at(y_it) = lerp(0.f, 1.f, temp1, temp2, diff);
                }
            }
        }

        // -----
        for(size_t y = 0; y < m_sizeInterpolated.height; y++){
            for(size_t x = 0; x < m_size.width - 1; x++){
                size_t x_it = x * (interpol + 1);

                for(size_t i = 0; i < interpol; i++){
                    std::float32_t temp1 = m_values.at(x_it).at(y);
                    std::float32_t temp2 = m_values.at(x_it + interpol + 1).at(y);

                    std::float32_t diff = (std::float32_t) (i + 1) / (interpol + 1);

                    m_values.at(x_it + i + 1).at(y) = lerp(0.f, 1.f, temp1, temp2, diff);
                }
            }
        }
    }

    void Grid::render(sf::RenderWindow* window, const unsigned int width, const unsigned int height){
        float x_size = (float) width / m_sizeInterpolated.width;
        float y_size = (float) height / m_sizeInterpolated.height;
        sf::Vector2f size(x_size, y_size);

        for(size_t x = 0; x < m_sizeInterpolated.width; x++){
            for(size_t y = 0; y < m_sizeInterpolated.height; y++){
                sf::RectangleShape rect;
                rect.setSize(size);
                rect.setPosition(sf::Vector2f(x * x_size, y * y_size));
                rect.setFillColor(hsv(
                                    lerp(   17, 
                                            30, 
                                            240, 
                                            0, 
                                            m_values.at(x).at(y)
                                        ), 
                                    1, 
                                    1
                                ));

                window->draw(rect);
            }
        }

        /*float x_size = (float) width / m_size.width;
        float y_size = (float) height / m_size.height;
        sf::Vector2f size(x_size, y_size);

        for(size_t x = 0; x < m_size.width; x++){
            for(size_t y = 0; y < m_size.height; y++){
                sf::RectangleShape rect;
                rect.setSize(size);
                rect.setPosition(sf::Vector2f(x * x_size, y * y_size));
                rect.setFillColor(hsv(
                                    lerp(   17, 
                                            30, 
                                            240, 
                                            0, 
                                            m_valueGrid.at(x).at(y)
                                        ), 
                                    1, 
                                    1
                                ));

                window->draw(rect);
            }
        }*/
    }
}