#pragma once 
#include "Includes.h"


class Grid{

    public:

    Grid();
    Grid(sf::Vector2u);


    void Update();
    void SetActive  (std::pair<int,int>);
    void SetInactive(std::pair<int,int>);
    void SetSize(sf::Vector2u);
    void SetRules();
    void Clear();

    std::set<std::pair<int,int>> GetActive();


    private:
    
    void Init(sf::Vector2u, float);
    int  GetAdjacent(int x, int y);
    bool IsValidCell(std::pair<int,int> cell);

        bool rules [9][2];
        sf::Vector2u size;

        std::vector<std::vector<bool>> map;
        std::set<std::pair<int,int>> active;
        // std::set<sf::Vector2f> inactive;
};