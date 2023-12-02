#include "Application.hpp"

namespace Application{
    Application::Application(){
    }

    bool Application::create(const int width, const int height, const std::string title){
        m_window.create(sf::VideoMode(width, height), title);

        if(!ImGui::SFML::Init(m_window))
            return false;
        
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

    void Application::run(int& current){
        ImGui::Begin("ThermalCamera");
        ImGui::SeparatorText("Select Input");
    
        const char* sensors[] = {"AMG8833", "MLX90640", "Mock Server", "Custom"};

        if(ImGui::Combo("Sensor", &current, sensors, IM_ARRAYSIZE(sensors))){
            std::cout << "geändert?" << std::endl;
        }

        ImGui::SeparatorText("EXPERIMENT");

        if(ImGui::BeginMenu("Test Menu")){
            if(ImGui::MenuItem("MenuItem1")){
                ImGui::TextColored(ImVec4(0.607, 0.635, 0.909, 1), "Hintergrundfarbe: ");
                ImGui::EndMenu();
            }
            if(ImGui::MenuItem("MenuItem2")){
                ImGui::TextColored(ImVec4(0.635, 0.606, 0.909, 1), "Vordergrundfarme: ");
                ImGui::EndMenu();
            }
        }

        ImGui::End();

        ImGui::ShowDemoWindow();

        m_window.clear();
        ImGui::SFML::Render(m_window);
        m_window.display();          
    }
}