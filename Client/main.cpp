#include <iostream>
#include <stdfloat>
#include <cstring>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "include/imgui/imgui.h"
#include "include/imgui/imgui-SFML.h"

#include "Network.hpp"

Network::Network network;
std::uint8_t data[Network::MAX_PACKET_SIZE];
size_t recv;


sf::RenderWindow window;

int main(){
    network.connect();

    window.create(sf::VideoMode(800, 800), "AMG88xx");

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                window.close();
        }

        if(!network.receive(data, &recv)){
            std::cout << "Error receiving packet!" << std::endl;
            while(true);
        }

        window.clear();

        for(size_t i = 0; i < 64; i++){
            std::float32_t f;
            std::memcpy(&f, &data[i * 4], sizeof(std::float32_t));
            
            std::cout << f << " ";

            if((i + 1) % 8 == 0)
                std::cout << std::endl;

            sf::RectangleShape rect(sf::Vector2f(100, 100));
            rect.setPosition((i % 8) * 100, ((int) (i / 8)) * 100);

            window.draw(rect);
        }

        std::cout << std::endl;

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