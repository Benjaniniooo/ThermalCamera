/*#include <iostream>
#include <stdfloat>
#include <cstring>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

//#include "include/imgui/imgui.h"
//#include "include/imgui/imgui-SFML.h"

#include "Network.hpp"

Network::Network network;
std::uint8_t data[Network::MAX_PACKET_SIZE];
size_t recv;

int width = 32;
int height = 24;

float lerp(float x1, float x2, float y1, float y2, float v){
    return (v - x1) * (y2 - y1) / (x2 - x1) + y1;
}

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


sf::RenderWindow window;

int main(){
    if(!network.connect()){
        std::cout << "Error connecting" << std::endl;
        return -1;
    }

        window.clear();

        auto val = network.receive(data, &recv);

        std::cout << recv << std::endl;

        if(val == sf::Socket::Done){
            float xsize = 800 / width;
            float ysize = 800 / height;

            for(size_t x = 0; x < width; x++){
                for(size_t y = 0; y < height; y++){
                    std::float32_t f;
                    std::memcpy(&f, &data[(y * width + x) * 4], sizeof(std::float32_t));

                    sf::RectangleShape rect(sf::Vector2f(xsize, ysize));
                    rect.setPosition(x * xsize, y * ysize);
                    rect.setFillColor(hsv(lerp(17, 30, 240, 0, f), 1, 1));

                    window.draw(rect);
                }
            }
        }
        window.display();

        sf::sleep(sf::seconds(0.01f));
    }
}*/

#include "Application.hpp"
#include "Grid.hpp"

Application::Application app;


int main(){
    Application::Application app;
    
    if(!app.create())
        exit(-1);

    int currentSensor = 0;

    while(app.isOpen()){
        app.handleEvents();
        app.run(currentSensor);
    }
    
    app.close();

    Grid::Grid g;
    g.create(Grid::MLX90640_ARRAY_SIZE);

}