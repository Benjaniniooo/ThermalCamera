#include "Application.hpp"
Application::Application app;

int main(){
    if(!app.create()){
        exit(-1);
    }
    
    while(app.isOpen()){
        app.handleEvents();
        app.run();
    }
    
    app.close();
}