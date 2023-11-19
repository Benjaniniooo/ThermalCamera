#include "Application.hpp"

namespace Application
{
    Application::Application(){
    }

    void Application::create(const int width, const int height, const std::string title){
        m_window.create(sf::VideoMode(width, height), title);
        ImGui::SFML::Init(m_window);
    }

    void Application::run(){
        while(m_window.isOpen()){
            ImGui::SFML::Update(m_window, m_deltaClock.restart());

            while(m_window.pollEvent(m_event)){
                ImGui::SFML::ProcessEvent(m_window, m_event);

                if(m_event.type == sf::Event::Closed)
                    m_window.close();
            }
        }

        ImGui::SFML::Shutdown();
    }
}