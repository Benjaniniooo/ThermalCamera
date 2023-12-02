#include "Application.hpp"

namespace Application{
    Application::Application(){
    }

    bool Application::create(const unsigned int width, const unsigned int height, const std::string title){
        m_width = width;
        m_height = height;   
        m_window.create(sf::VideoMode(m_width, m_height), title);

        if(!ImGui::SFML::Init(m_window))
            return false;
        
        //ToDo
        if(!m_network.connect())
            return false;

        m_grid.create(Grid::MOCK_SERVER_ARRAY_SIZE);

        return true;
    }

    void Application::handleEvents(){
        while(m_window.pollEvent(m_event)){
            ImGui::SFML::ProcessEvent(m_window, m_event);

            if(m_event.type == sf::Event::Resized){
                m_width = m_event.size.width;
                m_height = m_event.size.height;

                m_window.setView(sf::View(sf::FloatRect(0, 0, m_width, m_height)));    
            }

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

        m_window.clear();
        ImGui::SFML::Render(m_window);
        m_window.display();          
    }
}