#include "./src/Network.hpp"

#define MIN_TEMP 18
#define MAX_TEMP 32

Network::Network net;

float values[64];

void setup(){
    Serial.begin(115200);

    if(!net.createAP())
        while(true);

    net.createServer();
}

void loop(){
    if(net.newClient()){
        Serial.println("New Client!");

        while(net.clientIsConnected()){
            for(size_t i = 0; i < 64; i++){
                values[i] = map(random(255), 0, 255, MIN_TEMP, MAX_TEMP);
            }

            net.sentPacket(values, sizeof(float) * 64);

            delay(500);
        }

        net.endClient();
        Serial.println("Client disconnected!");
    }
}