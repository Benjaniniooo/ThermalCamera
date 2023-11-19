#include <iostream>
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

    window.create(sf::VideoMode(800, 800), "AMG88xx");


    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        auto val = network.receive(data, &recv);

        std::cout << recv << std::endl;

        if(val == sf::Socket::Done){
            /*for(size_t i = 0; i < width * height; i++){
                std::float32_t f;
                std::memcpy(&f, &data[i * 4], sizeof(std::float32_t));

                float xsize = 800 / width;
                float ysize = 800 / height;
                sf::RectangleShape rect(sf::Vector2f(xsize, ysize));

                float xposition = (i % width);
                float yposition = ((int)(i / height));
                rect.setPosition(xposition * xsize, yposition * ysize);
                rect.setFillColor(hsv(lerp(17, 30, 240, 0, f), 1, 1));

                std::cout << i << " " << xposition << " " << yposition << std::endl; 

                window.draw(rect);

                if((i + 1) % width == 0)
                    std::cout << std::endl;
            }*/
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
}

/*int main() {
    sf::RenderWindow window(sf::VideoMode(640, 480), "ImGui + SFML = <3");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Hello, world!");
        ImGui::Button("Look at this pretty button");
        ImGui::End();

        window.clear();
        window.draw(shape);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}*/