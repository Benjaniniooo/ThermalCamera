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
#include <SFML/System.hpp>

#include <iostream>
#include <cinttypes>
#include <array>

namespace Network{
    const std::string SERVER_ADDRESS = "192.168.4.1";
    const unsigned int SERVER_PORT = 80;

    const int MAX_PACKET_SIZE = 64 * 64 * sizeof(std::uint32_t);

    class Network{
        public:
            Network();

            bool connect(const std::string address, const unsigned int port);
            bool connect();
            void disconnect();

            std::string& getAddress();
            unsigned int& getPort();

            std::string m_address;
            unsigned int m_port;
        private:
            sf::TcpSocket m_tcpSocket;
    };
}