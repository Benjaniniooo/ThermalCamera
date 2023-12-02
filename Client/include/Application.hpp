#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "./imgui/imgui.h"
#include "./imgui/imgui-SFML.h"
#include "./imgui/imgui_stdlib.h"

#include "Grid.hpp"
#include "Network.hpp"

namespace Application{
    const unsigned int WINDOW_WIDTH = 800;
    const unsigned int WINDOW_HEIGHT = 800;

    const std::string WINDOW_TITLE = std::string("ThermalCamera");

    class Application{
        public:
            Application();

            bool create(const unsigned int width = WINDOW_WIDTH, 
                        const unsigned int height = WINDOW_HEIGHT, 
                        const std::string title = WINDOW_TITLE);
            void handleEvents();
            bool isOpen();
            void run();
            void close();

        private:
            sf::RenderWindow m_window;
            unsigned int m_width, m_height;
            sf::Event m_event;

            sf::Clock m_deltaClock;

            Network::Network m_network;

            //IMGUI
            bool m_showSettingsPage;
            bool m_showRenderPage;
    };
}
