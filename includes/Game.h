#pragma once
#include "Includes.h"
#include "Grid.h"

class Game{

    public: 

    Game();
    Game(sf::Vector2i size, float scale);

    void Run();
    void Pause();


    private:
    
    void Init();
    void Update();
    void HandleInputs();

        Grid grid;

        sf::RenderWindow window;
        bool is_running;

};