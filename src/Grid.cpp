#include "Grid.h"

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- CONSTRUCTOR / DESTRUCTOR -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    Grid::Grid(){
        size = sf::Vector2u(15,10);
        scale = 10;
    }


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- PUBLIC  FUNCTIONS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    // rules: 
    // dead + 2/3 alive -> alive
    // alive + <2 & >3 alive -> dead
    // 
    void Grid::Update(){
        
        std::vector<sf::Vector2i> changes;
        int count;
        for (int i=0; i<size.x; i++){
            for (int j=0; j<size.y; j++){
                count = GetAdjacent(i,j);
                // die cond
                if ( map[i][j] && (count < 2 || count > 3))
                    changes.push_back(sf::Vector2i(i,j));
                
                // new born cond
                if (!map[i][j] && count == 3)
                    changes.push_back(sf::Vector2i(i,j));

            }
        }
        for (auto c : changes){
            if(map[c.x][c.y])
                map[c.x][c.y]=0;
            else
                map[c.x][c.y]=1;
        }                
    }

    void Grid::Draw (sf::RenderWindow* window){
        window->clear();
        
        sf::RectangleShape shape;
        shape.setSize(sf::Vector2f(scale-2,scale-2));
        shape.setFillColor(sf::Color::Green);
        
        for (int i=0; i<size.x; i++){
            for (int j=0; j<size.y; j++){
                if(map[i][j]){
                    shape.setPosition(sf::Vector2f(i*scale+1,j*scale+1));
                    window->draw(shape);
                }
            }
        }

        window->display();

    }
    
    void Grid::SetActive(std::pair<int,int> cell){

        if (cell.first < size.x && cell.second < size.y){
            map[cell.first][cell.second] = true; 
            active.insert(cell);
        }
    }

    void Grid::SetSize(sf::Vector2u new_size){

        // clear map
        map.clear();
        
        // resize
        map.resize(new_size.x);
        for (int i=0; i < new_size.x; i++)
            map[i].resize(new_size.y);
        
        // add active nodes
        for (auto cell : active){
            map[cell.first][cell.second] = true;
        }

    }

    void Grid::Clear(){
        map.clear();
        
        // resize
        map.resize(size.x);
        for (int i=0; i < size.x; i++)
            map[i].resize(size.y);
        
        active.clear();
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- PRIVATE FUNCTIONS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/


    void Grid::Init(sf::Vector2u grid_size, float grid_scale){
        if (grid_size.x > 0 && grid_size.y > 0)
            size = grid_size;
        if (grid_scale > 0)
            scale = grid_scale;
        SetSize(size);
    }   

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