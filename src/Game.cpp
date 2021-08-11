#include "Game.h"

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- CONSTRUCTOR / DESTRUCTOR -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    Game::Game (): is_running(false), scale(10){
        InitWindow();
        std::cout<<UPDATE_TRESHOLD;
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- PUBLIC  FUNCTIONS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    void Game::Run(){
        while (window.isOpen()){
            
            DELTA_TIME = clock.getElapsedTime().asSeconds();
            clock.restart();
            
            UPDATE_TIMER += DELTA_TIME;
            RENDER_TIMER += DELTA_TIME;

            if (UPDATE_TIMER >= UPDATE_TRESHOLD){
                UPDATE_TIMER = 0;
                Update();
            }
            if (RENDER_TIMER >= RENDER_TRESHOLD){
                RENDER_TIMER = 0;
                Draw();
            }

            HandleInputs();
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
        std::cout<<UPDATE_TRESHOLD<<"\n";
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
                        if (UPDATE_TRESHOLD > 0.034) UPDATE_TRESHOLD -= 0.05;
                    
                    if (event.key.code == sf::Keyboard::E)
                        if (UPDATE_TRESHOLD < 0.40) UPDATE_TRESHOLD += 0.05;

                    if (event.key.code == sf::Keyboard::Escape)
                        window.close();
                    break;
                }

                // Mouse wheel zoom + Grid resize 
                case sf::Event::MouseWheelScrolled:{
                    if (scale > 3.5 && event.mouseWheelScroll.delta == -1)
                        scale -= scale/10;
                    if (scale < 50  && event.mouseWheelScroll.delta ==  1)
                        scale += scale/10;

                    sf::Vector2u grid_rescale = window.getSize();
                    grid_rescale.x /= scale;
                    grid_rescale.y /= scale;
                    grid.SetSize(grid_rescale);
                    break;
                }

                // grid * scale = window
                case sf::Event::Resized:{   //BAD!   - ADD VIEW HERE -
                    // sf::Vector2u grid_rescale = window.getSize();
                    // grid_rescale.x /= scale;
                    // grid_rescale.y /= scale;
                    // grid.SetSize(grid_rescale);                    
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