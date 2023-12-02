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
    }

    void Grid::create(const ARRAY_SIZE size){
        m_valueGrid.resize(size.width, std::vector<std::float32_t>(size.height, 0.f));

        m_size = size;
    }

    void Grid::copyDataFromRawBuffer(const std::uint8_t* data, const size_t size){
        //convert buffer size to iterator size (one piece of information is 4 bytes or 1 std::float32_t long)
        size_t size_it = size / sizeof(std::float32_t);

        for(size_t i = 0; i < size_it && i < m_size.width * m_size.height; i++){
            int x = (int) (i / m_size.width);
            int y = i % m_size.height;

            //copy four bytes of data from the buffer to the valueGrid at (x,y) and bitcast it to a std::float32_t
            std::memcpy(&m_valueGrid.at(x).at(y), &data[i * 4], sizeof(std::float32_t));
        }
    }

    void Grid::render(sf::RenderWindow* window, const unsigned int width, const unsigned int height){
        float x_size = width / m_size.width;
        float y_size = height / m_size.height; 

        std::cout << window->getSize().x << " " << window->getSize().y << std::endl;

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
        }
    }
}