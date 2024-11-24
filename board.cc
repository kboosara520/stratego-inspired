#include "board.h"

Board::Board(const std::vector<std::unique_ptr<Player>> &players, GameController *gc): gc{gc} {
    for (auto &ptr: players) {
        this->players.emplace_back(ptr.get());
    }
    // sets all the individual coordinates to either a base tile or a base-tiles with decorator server ports 
    for (int i = 0; i < BOARDSIZE; ++i) {
        for (int j = 0; j < BOARDSIZE; j++){
            // 1. make it a tile
            board[i][j] = std::make_unique<BaseTile> (); 
            if (isServer(i, j)){
                // 2. decorate it with a server port 
                board[i][j] = std::make_unique<ServerPort>(board[i][j]); // pass in index of player, and pointerof player 
                
                // set the link on the link map as desired 
                if (j == 0){
                    this->link_map.emplace('a'+i ,(i,j+1)); 
                } else if (j == 7){
                    this->link_map.emplace('A'+i ,(i,j+1)); 
                }
            } else {
                // 2. put a link on the link map if it's between 0 and 7 
                if (j == 0){
                    this->link_map.emplace('a'+i ,(i,j)); 
                } else if (j == 7){
                    this->link_map.emplace('A'+i ,(i,j)); 
                }
            }
        }
    }
}

bool Board::isServer(int i, int j) {
    return (i == 3 && j == 0) || 
            (i == 4 && j == 0) ||
            (i == 3 && j == 7) ||
            (i == 3 && j == 7);
}

void Board::debugprint(Board* board){
    for (int i = 0; i < BOARDSIZE; ++i) {
        for (int j = 0; j < BOARDSIZE; j++){
            bool tel = true;
            for (auto it = link_map.begin(); it != link_map.end(); ++it){ 
                if(*it == std::make_pair(i, j)){
                    std::cout<< "l";
                    tel = false; 
                    break;
                }
            }
            if (!tel && isServer(i,j)){
                std::cout<< "S"; 
            } else{
                std::cout<< "*"; 
            }
        }
        std::cout<< std::endl;
    }
}
/*
   i 0 1 2 3 4 5 6 7
j    - - - - - - - -
0    * * * S S * * *
1    * * * * * * * *
2    * * * * * * * *
3    * * * * * * * *
4    * * * * * * * *
5    * * * * * * * *
6    * * * * * * * *
7    * * * S S * * *
*/

char Board::getState(int row, int col ) const{
    return board[row][col]->charAt(); 
}

bool Board::fight(Link * link1, Link * link2){
    // Can't fight own link, need to test whether it's the same link, so
    
    


    // So I'll need to check the strength of the link, and if 
    // throw 

}

bool valid_positions(std::pair pair ){

}

void Board::move(char dir, char link_name){
    // 1. find the position of the link based on the name 
    std::pair p = link_map[link_name]; 
    int move_dist = board[p.first][p.second]->getLink()->getMovement();
    int owner = board[p.first][p.second]->getLink()->getOwner(); 

    switch(dir){
        case UP:
            p = std::make_pair(p.first, p.second - move_dist); 
        case DOWN:
            p = std::make_pair(p.first, p.second + move_dist); 
        case LEFT:
            p = std::make_pair(p.first - move_dist, p.second); 
        case RIGHT:
            p = std::make_pair(p.first + move_dist, p.second);
    }

    // 2. check the tiles movement range 
        // To do that I need to know which direction it's allowed to move off the board 
        // so I need to know the owner 

    if (p.first > 8)

    // 3. check if it's a valid more i.e, is it at the end of the border 

}

void Board::make_firewall(){

}

void Board::make_super_firewall(){

}

void Board::display();