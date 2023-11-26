#include "Network.hpp"

namespace Network{
    Network::Network(){};

    bool Network::connect(const sf::IpAddress ip_address, const int port, const sf::Time timeOut){
        m_tcpSocket.setBlocking(false);
        if(m_tcpSocket.connect(ip_address, port, timeOut) != sf::Socket::Done){
            return false;
        }

        return true;
    }

    bool Network::receive(std::uint8_t* data, size_t* recv, int max_packet_size){
        if(m_tcpSocket.receive(data, max_packet_size, *recv) != sf::Socket::Done){
            return false;
        }

        return true;
    }
}