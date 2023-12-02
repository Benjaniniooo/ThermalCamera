#include "Network.hpp"

namespace Network{
    Network::Network()
        : m_address(SERVER_ADDRESS)
        , m_port(SERVER_PORT)
    {
        m_tcpSocket.setBlocking(false);
    }

    bool Network::connect(const std::string address, const unsigned int port){
        m_address = address;
        m_port = port;

        return connect();

    }

    bool Network::connect(){
        sf::IpAddress ipAddress(m_address);

        if(m_tcpSocket.connect(ipAddress, m_port) != sf::Socket::Done){
            return false;
        }
        return true;
    }

    void Network::disconnect(){
        m_tcpSocket.disconnect();
    }

    std::string& Network::getAddress(){
        return m_address;
    }
}

/*namespace Network{
    bool Network::receive(std::uint8_t* data, size_t* recv, int max_packet_size){
        if(m_tcpSocket.receive(data, max_packet_size, *recv) != sf::Socket::Done){
            return false;
        }

        return true;
    }
}*/