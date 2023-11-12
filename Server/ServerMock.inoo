#include <WiFi.h>

const char* SSID = "AMG88xx";
const char* passphrase = "AMG-8833";
const int port = 80;

WiFiServer server;

void setup(){
    Serial.begin(115200);

    if(!WiFi.softAP(SSID, passphrase)){
        log_e("Cannon create Soft Access Point");
        while(true);
    }

    Serial.print("IP: ");
    Serial.println(WiFi.softAPIP());

    server.begin(port);
}

void loop(){
    WiFiClient client = server.available();

    if(client){
        Serial.println("New Client!");

        while(client.connected()){
            client.write((byte*) &amg.m_pixels, 4 * 64);

            delay(500);
        }

        client.stop();
        Serial.println("Client disconnected!");
    }
}