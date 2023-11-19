#include <WiFi.h>

#include "./src/Network.hpp"
Network::Network net;

const int delayTime = 500;

#define MLX_90640
//#define AMG_88xx
//#define MOCK_SERVER

#ifdef MLX_90640
    #include "./src/MLX90640.hpp"
    MLX90640::MLX90640 mlx;
    
    void initialise(){
        if(!mlx.begin())
            exit(0);

        if(!net.createAP(F("MLX90640"), F("MLX90640")))
            exit(0);
    }

    void run(){
        mlx.pollPixels();
        net.sentPacket(mlx.m_pixels, sizeof(float) * MLX90640::MLX90640_PIXEL_WIDTH * MLX90640::MLX90640_PIXEL_HEIGHT);
    }
#endif

#ifdef AMG_88xx
    #include "./src/AMG88xx.hpp"
    AMG88xx::AMG88xx amg;
    
    void initialise(){
        if(!amg.begin())
            exit(0);

        if(!net.createAP(F("AMG8833"), F("AMG-8833")))
            exit(0);
    }
    
    void run(){
        amg.pollPixels();
        net.sentPacket(amg.m_pixels, sizeof(float) * AMG88xx::AMG88xx_PIXEL_WIDTH * AMG88xx::AMG88xx_PIXEL_HEIGHT);
    }
#endif

#ifdef MOCK_SERVER
    const int pixel_width = 8;
    const int pixel_height = 8;
    float pixel[pixel_width * pixel_height];

    const int min_temp = 17;
    const int max_temp = 32;

    void initialise(){
        if(!net.createAP(F("MOCKSERVER"), F("MOCKSERVER")))
            exit(0);
    }

    void run(){
        for(size_t x = 0; x < pixel_width; x++){
            for(size_t y = 0; y < pixel_height; y++){
                pixel[y * pixel_width + x] = map(random(255), 0, 255, min_temp, max_temp);
            }
        }

        net.sentPacket(pixel, sizeof(float) * pixel_width * pixel_height);
    }
#endif

void setup(){
    initialise();

    net.createServer();
}

void loop(){
    if(net.newClient()){
        while(net.clientIsConnected()){
            run();
           
            delay(delayTime);
        }

        net.endClient();
    }
}