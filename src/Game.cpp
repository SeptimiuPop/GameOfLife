#include "Game.h"

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- CONSTRUCTOR / DESTRUCTOR -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    Game::Game (): is_running(false){
                   Init();
    }
    
    Game::Game (sf::Vector2i size_d, float scale_d): 
                is_running(false){
                Init();
    } 

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- PUBLIC  FUNCTIONS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    void Game::Run(){
        while (window.isOpen()){
            Update();
            HandleInputs();
        }
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- PRIVATE FUNCTIONS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    void Game::Init(){
        window.create(sf::VideoMode(1500, 1000), "Hello", sf::Style::Default);
        grid.Init(sf::Vector2u(150,100), 10);
    }

    /*
    *
    * close window
    * detect inputs 
    * start / pause game
    * rezise
    * editor (drawing) mode with mouse 
    * 
    */
    void Game::Update(){
        if (is_running){
            grid.Update();
        }
        grid.Draw(&window);

    }

    void Game::HandleInputs(){
        sf::Event ev;

        while (window.pollEvent(ev)){

            switch (ev.type){

                // Close Button event 
                case sf::Event::Closed:
                    window.close();
                    break;
                
                // KeyReleased event 
                case sf::Event::KeyReleased:{
                    if (ev.key.code == sf::Keyboard::Space)
                        is_running = !is_running;
                    
                    if (ev.key.code == sf::Keyboard::S)
                        {grid.Update(); grid.Draw(&window);}

                    if (ev.key.code == sf::Keyboard::C)
                        grid.Clear();

                    if (ev.key.code == sf::Keyboard::Escape)
                        window.close();
                    break;
                }

                default: 
                    break;
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            sf::Vector2i mouse = sf::Mouse::getPosition(window);
            std::pair<int,int> pos(mouse.x/10, mouse.y/10);
            grid.SetActive(pos);
        }
    }