#include "Network.hpp"

namespace Network{
    Network::Network()
        : m_address(SERVER_ADDRESS)
        , m_port(SERVER_PORT)
        , m_received_bytes(0)
        , m_connectionStatus(CONNECTION_STATUS::Disconnected)
    {   
        std::fill(m_buffer, m_buffer + BUFFER_SIZE, 0);

    }

    bool Network::connect(const std::string address, const unsigned int port){
        m_address = address;
        m_port = port;

        return connect();

    }

    bool Network::connect(){
        sf::IpAddress ipAddress(m_address);

        if(m_tcpSocket.connect(ipAddress, m_port, sf::seconds(1.f)) == sf::Socket::Done){
            m_connectionStatus = CONNECTION_STATUS::Connected;
            m_tcpSocket.setBlocking(false);

            return true;
        }

        return false;
    }

    void Network::disconnect(){
        m_connectionStatus = CONNECTION_STATUS::Disconnected;
        m_tcpSocket.setBlocking(true);
        m_tcpSocket.disconnect();
    }

    bool Network::receive(){
        if(m_tcpSocket.receive(&m_buffer, BUFFER_SIZE, m_received_bytes) == sf::Socket::Done){
            return true;
        }

        return false;
    }
}