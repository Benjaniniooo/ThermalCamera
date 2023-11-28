#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "./imgui/imgui.h"
#include "./imgui/imgui-SFML.h"

#include <iostream>

namespace Application{
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 800;

    const std::string WINDOW_TITLE = std::string("ThermalCamera");

    class Application{
        public:
            Application();

            bool create(const int width = WINDOW_WIDTH, 
                        const int height = WINDOW_HEIGHT, 
                        const std::string title = WINDOW_TITLE);
            void handleEvents();
            bool isOpen();
            void run();
            void close();

        private:
            sf::RenderWindow m_window;
            sf::Event m_event;

            sf::Clock m_deltaClock;
    };
}
