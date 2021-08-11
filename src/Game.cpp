#include "Game.h"

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- CONSTRUCTOR / DESTRUCTOR -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    Game::Game (): is_running(false), scale(10){
        InitWindow();
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- PUBLIC  FUNCTIONS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    void Game::Run(){
        while (window.isOpen()){
            
            DELTA_TIME += clock.getElapsedTime().asSeconds();
            clock.restart();
            
            if (DELTA_TIME >= UPDATE_TRESHOLD){
                Update();
                DELTA_TIME = 0;
            }
            HandleInputs();
            Draw();
        }
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- PRIVATE FUNCTIONS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    void Game::InitWindow(){
        window.create(sf::VideoMode(1500, 1000), "Game Of Life - alpha 1.2", sf::Style::Default);
    }


    void Game::Draw (){
        window.clear();
        
        sf::RectangleShape shape;
        shape.setSize(sf::Vector2f(scale-2,scale-2));
        shape.setFillColor(sf::Color::Green);
        
        std::set<std::pair<int,int>> active = grid.GetActive(); 

        for (auto cell : active){
            shape.setPosition(sf::Vector2f(cell.first*scale+1, cell.second*scale+1));
            window.draw(shape);
        }

        window.display();

    }

    void Game::Update(){
        // Internal grid not "paused"
        if (is_running){
            grid.Update();
        }
    }

    void Game::HandleInputs(){

        while (window.pollEvent(event)){

            switch (event.type){

                // Close Button event 
                case sf::Event::Closed:
                    window.close();
                    break;
                
                // KeyReleased event 
                case sf::Event::KeyReleased:{
                    if (event.key.code == sf::Keyboard::Space)
                        is_running = !is_running;
                    
                    if (event.key.code == sf::Keyboard::S)
                        grid.Update(); 

                    if (event.key.code == sf::Keyboard::C)
                        grid.Clear();
                    
                    if (event.key.code == sf::Keyboard::Q)
                        if (UPDATE_TRESHOLD > 0.05) UPDATE_TRESHOLD -= 0.05;
                    
                    if (event.key.code == sf::Keyboard::E)
                        if (UPDATE_TRESHOLD < 0.5) UPDATE_TRESHOLD += 0.05;

                    if (event.key.code == sf::Keyboard::Escape)
                        window.close();
                    break;
                }

                // Mouse Wheel Zoom
                case sf::Event::MouseWheelScrolled:{
                    scale += event.mouseWheelScroll.delta;
                    break;
                }

                default: 
                    break;
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left ))
            grid.SetActive(MousePosToPair());

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            grid.SetInactive(MousePosToPair());
    }



    std::pair<int,int> Game::MousePosToPair(){
        
        sf::Vector2i mouse = sf::Mouse::getPosition(window);
        
        std::pair<int,int> pos;
        pos.first  = int(mouse.x/scale);
        pos.second = int(mouse.y/scale);
        
        return pos;
    }