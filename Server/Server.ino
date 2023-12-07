#include <WiFi.h>

#include "./src/Network.hpp"
Network::Network net;

const int delayTime = 250;

//#define MLX_90640
//#define AMG_88xx
#define MOCK_SERVER

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
    const int pixel_width = 16;
    const int pixel_height = 16;
    float pixel[pixel_width * pixel_height];

    const int min_temp = 17;
    const int max_temp = 32;

    int iter = 0;
    const int amount = 4;

    void initialise(){
        if(!net.createAP(F("MOCKSERVER"), F("MOCKSERVER")))
            exit(0);
    }

    void run(){
        for(size_t x = 0; x < pixel_width; x++){
            for(size_t y = 0; y < pixel_height; y++){
              if(iter > amount * 4){
                pixel[y * pixel_width + x] = map(random(255), 0, 255, min_temp, max_temp);
              }else if(iter > amount * 3){
                pixel[y * pixel_width + x] = (float) (x * y) / (pixel_width * pixel_height) * 255;
              }else if(iter > amount * 2){
                pixel[y * pixel_width + x] = (float) (x) / (pixel_width) * 255;
              }else if(iter > amount){
                pixel[y * pixel_width + x] = (float) (y) / (pixel_height) * 255;
              }else{
                pixel[y * pixel_width + x] = 255;
              }
            }
        }

        iter++;
        if(iter > amount * 5){
          iter = 0;
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