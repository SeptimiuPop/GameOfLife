#pragma once
#include "Includes.h"
#include "Grid.h"

class Game{

    public: 

    Game();

    void Run();
    void Pause();


    private:
    
    void InitWindow();
    void Draw();
    void Update();
    void HandleInputs();
    std::pair<int,int> MousePosToPair();

        Grid grid;

        sf::RenderWindow window;
        sf::Event event;
        bool is_running;

        float scale;

        sf::Clock clock;
        float UPDATE_TRESHOLD = 0.05;
        float DELTA_TIME = 0;
};