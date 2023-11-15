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

float lerp(float x1, float x2, float y1, float y2, float v){
    return (v - x1) * (y2 - y1) / (x2 - x1) + y1;
}

sf::Color hsv(int hue, float sat, float val)
{
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
    if(network.connect() != sf::Socket::Done){
        std::cout << "Error connecting" << std::endl;
        while(true);
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

        if(val == sf::Socket::Done){
            for(size_t i = 0; i < 64; i++){
                std::float32_t f;
                std::memcpy(&f, &data[i * 4], sizeof(std::float32_t));
            
                std::cout << f << " ";

                if((i + 1) % 8 == 0)
                    std::cout << std::endl;

                sf::RectangleShape rect(sf::Vector2f(100, 100));
                rect.setPosition((i % 8) * 100, ((int) (i / 8)) * 100);
                rect.setFillColor(hsv(lerp(17, 30, 240, 0, f), 1, 1));

                window.draw(rect);
            }

            std::cout << std::endl;
        }
        window.display();
    }

    window.close();
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