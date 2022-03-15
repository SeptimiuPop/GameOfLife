#include "Game.h"
#include <string>

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- CONSTRUCTOR / DESTRUCTOR -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    Game::Game (): is_grid_running(false), scale(10){
        InitWindow();
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- PUBLIC  FUNCTIONS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    void Game::Run(){
        while (window.isOpen()){
            if(window.hasFocus()){
                DELTA_TIME = clock.getElapsedTime().asSeconds();
                clock.restart();
                
                UPDATE_TIMER += DELTA_TIME;
                RENDER_TIMER += DELTA_TIME;

                if (RENDER_TIMER >= RENDER_TRESHOLD){
                    RENDER_TIMER = 0;
                    Draw();
                }
                if (UPDATE_TIMER >= UPDATE_TRESHOLD){
                    UPDATE_TIMER = 0;
                    Update();
                }

                HandleInputs();

            }
        }
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- PRIVATE FUNCTIONS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    void Game::InitWindow(){
        window.create(sf::VideoMode(1500, 900), "Game Of Life - alpha 1.2", sf::Style::Default);
    }


    void Game::Draw (){
        window.clear();
        
        sf::RectangleShape shape;
        shape.setSize(sf::Vector2f(scale-2,scale-2));
        shape.setFillColor(sf::Color::Green);
        

        for (auto cell : grid.GetActive()){
            shape.setPosition(sf::Vector2f(cell.first*scale+1, cell.second*scale+1));
            window.draw(shape);
        }

        DrawFPS();

        window.display();
    }

    void Game::DrawFPS(){
        sf::RectangleShape shape;
        shape.setSize(sf::Vector2f(125, 20));
        shape.setFillColor(sf::Color::Black);
        shape.setPosition(sf::Vector2f(0,0));

        sf::Text text;
        sf::Font font;
        font.loadFromFile("./assets/open-sans/OpenSans-Bold.ttf");
        text.setFont(font);
        text.setCharacterSize(15);
        text.setPosition(sf::Vector2f(0,0));
        
        std::string pi = "FPS: ";
        pi.append(std::to_string(DELTA_TIME));
        
        if (DELTA_TIME > 1/30.f)
            text.setFillColor(sf::Color::Red);
        else if (DELTA_TIME > 1/60.f)
            text.setFillColor(sf::Color::Yellow);
        else
            text.setFillColor(sf::Color::Green);

        text.setString(pi);
        window.draw(shape);
        window.draw(text);
    }

    void Game::Update(){
        // Internal grid not "paused"
        if (is_grid_running){
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
                        is_grid_running = !is_grid_running;
                    
                    if (event.key.code == sf::Keyboard::S)
                        if (!is_grid_running)
                            grid.Update(); 

                    if (event.key.code == sf::Keyboard::C)
                        grid.Clear();
                    
                    if (event.key.code == sf::Keyboard::Q)
                        if (UPDATE_TRESHOLD > 0.017) UPDATE_TRESHOLD -= 0.05;
                    
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