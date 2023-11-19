////////////////////////////////////////////////////////////
/// \file Network.hpp
/// \author Benjaniniooo (39649250+Benjaniniooo@users.noreply.github.com)
/// \brief A Wrapper for the ESP32 Network library
/// \version 0.1
/// \date 2023-11-14
/// 
/// @copyright Copyright (c) 2023
/// 
////////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <WiFi.h>


namespace Network{
    const String SSID = "ThermalCamera";
    const String PASSPHRASE = "crypticPassword";
    const int PORT = 80;


    ////////////////////////////////////////////////////////////
    /// \brief Wrapper for the WiFiServer, an accepted client and a 
    /// Soft Access Point
    /// 
    ////////////////////////////////////////////////////////////
    class Network{
        public:
            ////////////////////////////////////////////////////////////
            /// \brief Default constructor
            /// 
            ////////////////////////////////////////////////////////////
            Network();

            ////////////////////////////////////////////////////////////
            /// \brief Create a Soft Access Point on the ESP32 that any client can connect to
            ///
            /// \param ssid         service set - unique name for the WLAN created
            /// \param passphrase   password for the WLAN
            /// \return true        if the creation of a SoftAP was successful
            ///
            ////////////////////////////////////////////////////////////
            bool createAP(  const String ssid = SSID, 
                            const String passphrase = PASSPHRASE);

            ////////////////////////////////////////////////////////////
            /// \brief Create a TCP socket and bind that socket to a specific port
            /// 
            /// \param port The port to bind the socket to
            ///
            ////////////////////////////////////////////////////////////
            void createServer(const int port = PORT);

            ////////////////////////////////////////////////////////////
            /// \brief Check for a new client and connect to it if possible
            /// 
            /// \return true    if there is a new client connected
            ///
            ////////////////////////////////////////////////////////////
            bool newClient();

            ////////////////////////////////////////////////////////////
            /// \brief Check if a client is still connected to the socket
            /// 
            /// \return true    if the client is still connected
            ///
            ////////////////////////////////////////////////////////////
            bool clientIsConnected();

            ////////////////////////////////////////////////////////////
            /// \brief End the connection to the client
            /// 
            /// If the connection to the client has expired or the client is not
            /// responding, you can call this function.
            /// It is advised to call this function only after clientIsConnected()
            /// has returned false. 
            /// 
            ////////////////////////////////////////////////////////////
            void endClient();

            void sentPacket(const float* data, const size_t size);

        private:
            ////////////////////////////////////////////////////////////
            // Member data
            ////////////////////////////////////////////////////////////
            WiFiServer m_server;
            WiFiClient m_client;
    };
} // namespace Network