#include <WiFi.h>

#include "./src/AMG88xx.hpp"
#include "./src/MLX90640.hpp"

#include "./src/Network.hpp"

//AMG88xx::AMG88xx amg;
MLX90640::MLX90640 mlx;

Network::Network net;

void setup(){
    Serial.begin(115200);

    if(!net.createAP())
        while(true);

    net.createServer();

    /*if(!amg.begin())
        while(true);*/

    if(!mlx.begin())
        while(true);
}

void loop(){
    if(net.newClient()){
        Serial.println("New Client!");

        while(net.clientIsConnected()){
            //amg.pollPixels();
            mlx.pollPixels();

            //net.sentPacket(amg.m_pixels, sizeof(float) * AMG88xx::AMG88xx_PIXEL_WIDTH * AMG88xx::AMG88xx_PIXEL_HEIGHT);
            net.sentPacket(mlx.m_pixels, sizeof(float) * MLX90640::MLX90640_PIXEL_WIDTH * MLX90640::MLX90640_PIXEL_HEIGHT);

            delay(500);
        }

        net.endClient();
        Serial.println("Client disconnected!");
    }
}
