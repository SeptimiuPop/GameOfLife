#pragma once
#include "Includes.h"
#include "Grid.h"

class Game{

    public: 

    Game();

    void Run();
    void Pause();


    private:
    
    void Init();
    void Update();
    void HandleInputs();

        Grid grid;
        sf::RenderWindow window;
        bool is_running;

        sf::Clock clock;
        float tresh_hold, delta_time;
};