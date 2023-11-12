#include "Network.hpp"

namespace Network{
    Network::Network()
    : m_server(WiFiServer(PORT))
    , m_client(WiFiClient()){}

    bool Network::createAP(const String ssid, const String passphrase){
        if(!WiFi.softAP(ssid, passphrase)){
            log_e("Cannot create Soft Access Point");

            return false;
        }

        return true;
    }
    
    void Network::createServer(const int port){
        m_server.begin(port);
    }

    bool Network::newClient(){
        m_client = m_server.available();

        if(m_client)
            return true;

        return false;
    }

    void Network::endClient(){
        m_client.stop();
    }

    bool Network::clientIsConnected(){
        return m_client.connected();
    }

    void Network::sentPacket(const float* data, size_t size){
        m_client.write((byte*) data, size);
    }
}
