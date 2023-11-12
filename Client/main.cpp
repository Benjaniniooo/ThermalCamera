#include <iostream>
#include <stdfloat>
#include <cstring>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Network.hpp"

Network::Network network;

int main(){
    network.connect();

    std::uint8_t data[Network::MAX_PACKET_SIZE];
    size_t recv;

    while(true){
        if(!network.receive(data, &recv)){
            std::cout << "Error receiving packet!" << std::endl;
            while(true);
        }

        for(size_t i = 0; i < 64; i++){
            std::float32_t f;
            std::memcpy(&f, &data[i * 4], sizeof(std::float32_t));
            
            std::cout << f << " ";

            if((i + 1) % 8 == 0)
                std::cout << std::endl;
        }

        std::cout << std::endl;
    }
}