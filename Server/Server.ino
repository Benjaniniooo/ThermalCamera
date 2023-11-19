#include <WiFi.h>

#include "./src/Network.hpp"
Network::Network net;

#define MLX_90640
//#define AMG_88xx
//#define Mock_Server

#ifdef MLX_90640
    #include "./src/MLX90640.hpp"
    MLX90640::MLX90640 mlx;
    
    void initialise(){
        if(!mlx.begin())
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
    }
    
    void run(){
        amg.pollPixels();
        net.sentPacket(amg.m_pixels, sizeof(float) * AMG88xx::AMG88xx_PIXEL_WIDTH * AMG88xx::AMG88xx_PIXEL_HEIGHT);
    }
#endif

void setup(){
    initialise();

    if(!net.createAP())
        while(true);

    net.createServer();
}

void loop(){
    if(net.newClient()){
        while(net.clientIsConnected()){
            run();
           
            delay(500);
        }

        net.endClient();
    }
}