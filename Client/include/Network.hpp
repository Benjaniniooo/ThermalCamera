////////////////////////////////////////////////////////////
/// \file Network.hpp
/// \author Benjaniniooo (39649250+Benjaniniooo@users.noreply.github.com)
/// \brief SFML Network Wrapper
/// \version 0.1
/// \date 2023-11-14
/// 
/// @copyright Copyright (c) 2023
/// 
////////////////////////////////////////////////////////////

#pragma once

#include <SFML/Network.hpp>

#include <iostream>
#include <cinttypes>

namespace Network
{
    const sf::IpAddress SERVER_IP_ADDRESS("192.168.4.1");
    const int SERVER_PORT = 80;

    const int MAX_PACKET_SIZE = 4 * 32 * 24;

    class Network{
        public:
            Network();

            bool connect(const sf::IpAddress ip_address = SERVER_IP_ADDRESS, const int port = SERVER_PORT);

            bool receive(std::uint8_t* data, size_t* recv, int max_packet_size = MAX_PACKET_SIZE);
        private:
            sf::TcpSocket m_tcpSocket;
    };
}