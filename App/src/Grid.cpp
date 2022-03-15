#include "Grid.h"

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- CONSTRUCTOR / DESTRUCTOR -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    Grid::Grid(){
        size = sf::Vector2u(150,100);
        SetSize(size);
        SetRules();          
    }

    Grid::Grid(sf::Vector2u grid_size){
        if (grid_size.x > 0 && grid_size.y > 0)
            size = grid_size;
        SetSize(size);
        SetRules();          
    }


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- PUBLIC  FUNCTIONS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    void Grid::Update(){
        
        std::vector<sf::Vector2i> changes;
        int count;
        for (int i=0; i<size.x; i++){
            for (int j=0; j<size.y; j++){
                
                count = GetAdjacent(i,j);
                
                // determine wether we use die cond or spawn cond
                bool alive = map[i][j];  
                
                if(rules[count][alive] != alive)
                    changes.push_back(sf::Vector2i(i,j));

            }
        }

        for (auto aux : changes){
            if (map[aux.x][aux.y]){
                map[aux.x][aux.y] =0;
                active.erase(std::pair<int,int>(aux.x,aux.y));
            }
            else{
                map[aux.x][aux.y] =1;
                active.insert(std::pair<int,int>(aux.x,aux.y));
            }
        }                
    }
    
    void Grid::SetActive(std::pair<int,int> cell){
        if(IsValidCell(cell)){
            map[cell.first][cell.second] = true; 
            active.insert(cell);
        }
    }

    void Grid::SetInactive(std::pair<int,int> cell){
        if(IsValidCell(cell)){
            map[cell.first][cell.second] = false; 
            active.erase(cell);
        }
    }

    void Grid::SetSize(sf::Vector2u new_size){
        
        size = new_size;
        // clear map
        map.clear();
        
        // resize
        map.resize(new_size.x);
        for (int i=0; i < new_size.x; i++)
            map[i].resize(new_size.y);
        
        // add active nodes
        std::set<std::pair<int,int>> inactive;
        for (auto cell : active){
            if(IsValidCell(cell))
                map[cell.first][cell.second] = true;
            else 
                inactive.insert(cell);
        }
        for (auto cell : inactive)
            active.erase(cell);
    }

    void Grid::Clear(){
        map.clear();
        
        // resets grid completley
        map.resize(size.x);
        for (int i=0; i < size.x; i++)
            map[i].resize(size.y);
        
        active.clear();
    }

    std::set<std::pair<int,int>> Grid::GetActive(){
        return active;
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- PRIVATE FUNCTIONS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
 

    int Grid::GetAdjacent(int x, int y){
        int count = 0;
        for (int i=x-1; i<=x+1; i++)
            for (int j=y-1; j<=y+1; j++)
                if(i>=0 && i<size.x && 
                   j>=0 && j<size.y &&
                   map[i][j] && !(i==x && j==y))
                    count ++;
                
        return count;
    }

    bool Grid::IsValidCell(std::pair<int,int> cell){
        // check if a cell fits in the current grid
        if (cell.first  < size.x && cell.first  >= 0 &&  
            cell.second < size.y && cell.second >= 0)
            return true;
        return false;
    }

    void Grid::SetRules(){
        
        for (int j=0; j<2; j++)
        for (int k=0; k<9; k++)
        rules[k][j] = 0;

        // spawn cond 
        // rules[0][0] = 1;
        // rules[1][0] = 1;
        // rules[2][0] = 1;
        rules[3][0] = 1;
        // rules[4][0] = 1;
        // rules[5][0] = 1;
        // rules[6][0] = 1;
        // rules[7][0] = 1;
        // rules[8][0] = 1;
        
        // live cond
        // rules[0][1] = 1;
        // rules[1][1] = 1;
        rules[2][1] = 1;
        rules[3][1] = 1;
        // rules[4][1] = 1;
        // rules[5][1] = 1;
        // rules[6][1] = 1;
        // rules[7][1] = 1;
        // rules[8][1] = 1;
    }