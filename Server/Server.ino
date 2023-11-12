#include <WiFi.h>

#include "./src/AMG88xx.hpp"
#include "./src/Network.hpp"

AMG88xx::AMG88xx amg;
Network::Network net;

void setup(){
    Serial.begin(115200);

    if(!net.createAP())
        while(true);

    net.createServer();

    if(!amg.begin())
        while(true);
}

void loop(){
    if(net.newClient()){
        Serial.println("New Client!");

        while(net.clientIsConnected()){
            amg.pollPixels();

            net.sentPacket(amg.m_pixels, sizeof(float) * 64);

            delay(500);
        }

        net.endClient();
        Serial.println("Client disconnected!");
    }
}