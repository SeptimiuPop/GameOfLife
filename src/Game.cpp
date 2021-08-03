#include "Game.h"

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- CONSTRUCTOR / DESTRUCTOR -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    Game::Game (): is_running(false), delta_time(0), tresh_hold(0.05){
                   Init();
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- PUBLIC  FUNCTIONS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    void Game::Run(){
        while (window.isOpen()){
            
            delta_time += clock.getElapsedTime().asSeconds();
            clock.restart();
            
            if (delta_time >= tresh_hold){
                Update();
                delta_time = 0;
            }

            HandleInputs();
        }
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- PRIVATE FUNCTIONS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    void Game::Init(){
        window.create(sf::VideoMode(1500, 1000), "Game Of Life - alpha 1.1", sf::Style::Default);
    }

    /*
    *   To do:
    * add time setting
    * add window size setting
    * 
    *   Extra: 
    * UI with instructions and adjustments
    * add view (so we can zoom in and explore the details)
    * 
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

                    if (ev.key.code == sf::Keyboard::Q)
                        if (tresh_hold > 0.05) tresh_hold -= 0.05;
                    
                    if (ev.key.code == sf::Keyboard::E)
                        if (tresh_hold < 1) tresh_hold += 0.05;

                    if (ev.key.code == sf::Keyboard::Escape)
                        window.close();
                    break;
                }

                default: 
                    break;
            }
        }

        sf::Vector2i mouse = sf::Mouse::getPosition(window);
        std::pair<int,int> pos(int(mouse.x/10), int(mouse.y/10));

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left )) {
            grid.SetActive(pos);
            grid.Draw(&window);
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            grid.SetInactive(pos);
            grid.Draw(&window);
        }
    }