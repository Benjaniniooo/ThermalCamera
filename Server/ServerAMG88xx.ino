#include <WiFi.h>

#include "./include/AMG88xx.hpp"

const char* SSID = "AMG88xx";
const char* passphrase = "AMG-8833";
const int port = 80;

WiFiServer server;

AMG88xx::AMG88xx amg;

void setup(){
    Serial.begin(115200);

    if(!WiFi.softAP(SSID, passphrase)){
        log_e("Cannon create Soft Access Point");
        while(true);
    }

    Serial.print("IP: ");
    Serial.println(WiFi.softAPIP());

    server.begin(port);

    if(!amg.begin()){
        while(true);
    }
}

void loop(){
    WiFiClient client = server.available();

    if(client){
        Serial.println("New Client!");

        while(client.connected()){
            amg.pollPixels();

            client.write((byte*) &amg.m_pixels, 4 * 64);

            delay(500);
        }

        client.stop();
        Serial.println("Client disconnected!");
    }
}