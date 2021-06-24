#pragma once 
#include "Includes.h"


class Grid{

    public:

    Grid();

    void Init(sf::Vector2u, float);

    void Update();
    void Draw(sf::RenderWindow*);
    void SetActive(std::pair<int,int>);
    void SetSize(sf::Vector2u);
    void Clear();


    private:
    
    int GetAdjacent(int x, int y);

        sf::Vector2u size;
        float scale;

        std::vector<std::vector<bool>> map;
        std::set<std::pair<int,int>> active;

};