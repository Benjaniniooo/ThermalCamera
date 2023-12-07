#include "Application.hpp"

namespace Application{
    Application::Application(){
        m_grid.create(32, 24);
        m_selectedSensor = 0;
    }

    bool Application::create(const unsigned int width, const unsigned int height, const std::string title){
        m_width = width;
        m_height = height;   
        m_window.create(sf::VideoMode(m_width, m_height), title);

        if(!ImGui::SFML::Init(m_window))
            return false;

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

            ImGui::EndMainMenuBar();
        }

        if(m_showSettingsPage){
            ImGui::Begin("Settings", &m_showSettingsPage);

            ImGui::SeparatorText("Sensoren");
        
            if(ImGui::RadioButton("MLX90640", &m_selectedSensor, 0)){
                m_grid.create(32, 24);
            }
            if(ImGui::RadioButton("AMG8833", &m_selectedSensor, 1)){
                m_grid.create(8, 8);
            }
            if(ImGui::RadioButton("MockServer", &m_selectedSensor, 2)){
                m_grid.create(16, 16);
            }

            ImGui::SeparatorText("Netzwerk");            

            ImGui::InputTextWithHint("IP Addresse", "localhost oder 192.168.4.1", &m_network.m_address);
            ImGui::InputInt("Port", (int*) &m_network.m_port, true);

            if(ImGui::Button("Verbinden")){
                m_network.connect();
            }
            ImGui::SameLine();
            if(ImGui::Button("Trennen")){
                m_network.disconnect();
            }
            
            if(m_network.m_connectionStatus == Network::CONNECTION_STATUS::Connected){
                ImGui::Text("Verbunden");
            }else if(m_network.m_connectionStatus == Network::CONNECTION_STATUS::Disconnected){
                ImGui::Text("Getrennt");
            }

            ImGui::Text(std::to_string(m_network.m_received_bytes).c_str());

            ImGui::SeparatorText("Temperaturen");

            ImGui::InputFloat("Min.", &m_grid.min_temp);
            ImGui::InputFloat("Max.", &m_grid.max_temp);

            ImGui::Checkbox("Alternative Farbgebung", &m_grid.alternativeColoring);

            ImGui::End();
        }

        m_window.clear();
        
        if(m_network.m_connectionStatus == Network::CONNECTION_STATUS::Connected){
            if(m_network.receive()){
                m_grid.copyDataFromRawBuffer(m_network.m_buffer, m_network.m_received_bytes);
                m_grid.interpolate();
            }
            m_grid.render(&m_window, m_width, m_height);
            sf::sleep(sf::milliseconds(50));
        }
        
        ImGui::SFML::Render(m_window);

        m_window.display();          
    }
}