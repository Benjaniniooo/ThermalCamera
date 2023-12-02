#include "Network.hpp"

namespace Network{
    Network::Network(){};

    bool Network::connect(const sf::IpAddress ip_address, const int port, const sf::Time timeOut){
        if(m_tcpSocket.connect(ip_address, port, timeOut) != sf::Socket::Done){
            return false;
        }

        m_tcpSocket.setBlocking(false);

        return true;
    }

    void Network::disconnect(){
        m_tcpSocket.disconnect();
    }

    bool Network::receive(std::uint8_t* data, size_t* recv, int max_packet_size){
        if(m_tcpSocket.receive(data, max_packet_size, *recv) != sf::Socket::Done){
            return false;
        }

        return true;
    }
}