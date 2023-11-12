#include <WiFi.h>

#define MIN_TEMP 18
#define MAX_TEMP 32

const char* SSID = "AMG88xx";
const char* passphrase = "AMG-8833";
const int port = 80;

WiFiServer server;

float values[64];

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
            for(size_t i = 0; i < 64; i++){
              values[i] = map(random(255), 0, 255, MIN_TEMP, MAX_TEMP);
            }

            client.write((byte*) &values, 4 * 64);

            delay(500);
        }

        client.stop();
        Serial.println("Client disconnected!");
    }
}