#include "Application.hpp"

namespace Application{
    Application::Application(){
    }

    void Application::create(const int width, const int height, const std::string title){
        m_window.create(sf::VideoMode(width, height), title);
        ImGui::SFML::Init(m_window);
    }

    /*void Application::run(){
            ImGui::SFML::Update(m_window, m_deltaClock.restart());

            if (ImGui::BeginMainMenuBar())
            {
                if (ImGui::BeginMenu("File"))
                {
                    if (ImGui::MenuItem("Open..", "Ctrl+O")) { std::cout << "HALLOO" << std::endl; }
                    if (ImGui::MenuItem("Save", "Ctrl+S"))   {}
                    if (ImGui::MenuItem("Close", "Ctrl+W"))  { }
                    ImGui::EndMenu();
                }
                ImGui::EndMainMenuBar();
            }

            ImGui::Begin("My First Tool");
            ImGui::Text("Hello, world %d", 123);
            if (ImGui::Button("Save")){
                std::cout << "Save Button" << std::endl;
            }          

            ImGui::End();            

            m_window.clear();
            ImGui::SFML::Render(m_window);
            m_window.display();
    }*/

    void Application::handleEvents(){
        while(m_window.pollEvent(m_event)){
            ImGui::SFML::ProcessEvent(m_window, m_event);

            if(m_event.type == sf::Event::Closed)
                m_window.close();
        }
    }

    bool Application::isOpen(){
        return m_window.isOpen();
    }

    void Application::close(){
        ImGui::SFML::Shutdown();
    }
}