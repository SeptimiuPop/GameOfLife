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
        bool is_grid_running;

        float scale;

        sf::Clock clock;
        float UPDATE_TRESHOLD = 1/60.f;
        float RENDER_TRESHOLD = 1/60.f;
        
        float UPDATE_TIMER = 0;
        float RENDER_TIMER = 0;
        
        float DELTA_TIME = 0;
};