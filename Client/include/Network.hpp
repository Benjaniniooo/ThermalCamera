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

#include <cinttypes>

#include <iostream>

namespace Network{
    const std::string SERVER_ADDRESS = "192.168.4.1";
    const unsigned int SERVER_PORT = 80;

    const int BUFFER_SIZE = 64 * 64 * sizeof(std::uint32_t);

    enum CONNECTION_STATUS{
        Connected,
        Disconnected
    };

    class Network{
        public:
            Network();

            bool connect(const std::string address, const unsigned int port);
            bool connect();
            void disconnect();

            bool receive();

            std::string m_address;
            unsigned int m_port;

            std::uint8_t m_buffer[BUFFER_SIZE];
            size_t m_received_bytes;
            CONNECTION_STATUS m_connectionStatus;

        private:
            sf::TcpSocket m_tcpSocket;         
    };
}