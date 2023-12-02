#include "Application.hpp"

namespace Application{
    Application::Application(){
    }

    bool Application::create(const int width, const int height, const std::string title){
        m_window.create(sf::VideoMode(width, height), title);

        if(!ImGui::SFML::Init(m_window))
            return false;
        
        if(!m_network.connect())
            return false;

        grid.create(Grid::MOCK_SERVER_ARRAY_SIZE);

        return true;
    }

    void Application::handleEvents(){
        while(m_window.pollEvent(m_event)){
            ImGui::SFML::ProcessEvent(m_window, m_event);

            if(m_event.type == sf::Event::Closed)
                m_window.close();
        }

        ImGui::SFML::Update(m_window, m_deltaClock.restart());
    }

    bool Application::isOpen(){
        return m_window.isOpen();
    }

    void Application::close(){
        ImGui::SFML::Shutdown();
    }

    void Application::run(){
        if(ImGui::BeginMainMenuBar()){
            ImGui::MenuItem("Settings", NULL, &m_showSettingsPage);
            ImGui::MenuItem("Rendering", NULL, &m_showRenderPage);

            ImGui::EndMainMenuBar();
        }

        if(m_showSettingsPage){
            ImGui::Begin("Settings", &m_showSettingsPage);

            ImGui::SeparatorText("Sensors");

            ImGui::SeparatorText("Network");

            ImGui::SeparatorText("Delay Time");

            ImGui::End();
        }

        /*const char* sensors[] = {"AMG8833", "MLX90640", "Mock Server", "Custom"};

        if(ImGui::Combo("Sensor", &current, sensors, IM_ARRAYSIZE(sensors))){
            std::cout << "geändert?" << std::endl;
        }
        */

       std::uint8_t data[Network::MAX_PACKET_SIZE];
        size_t recv;

        if(m_network.receive(data, &recv)){
            std::cout << "\n\n received \n" << recv << std::endl;
            m_grid.copyDataFromRawBuffer(data, recv);
        }

        m_window.clear();
        ImGui::SFML::Render(m_window);
        m_grid.render(&m_window);
        m_window.display();          
    }
}