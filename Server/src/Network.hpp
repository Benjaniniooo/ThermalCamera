#include <WiFi.h>

namespace Network{
    const String SSID = "ThermalCamera";
    const String PASSPHRASE = "crypticPassword";
    const int PORT = 80;

    class Network{
        public:
            Network();

            bool createAP(const String ssid = SSID, const String passphrase = PASSPHRASE);
            void createServer(const int port = PORT);

            bool newClient();
            void endClient();
            bool clientIsConnected();

            void sentPacket(const float* data, const size_t size);
        private:
            WiFiServer m_server;
            WiFiClient m_client;
    };
}