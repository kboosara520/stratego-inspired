#include "board.h"
#include "constants.h"
#include "basetile.h"
#include "serverport.h"

Board::Board(const std::vector<std::unique_ptr<Player>> &players, GameController *gc): gc{gc} {
    for (auto &ptr: players) {
        this->players.emplace_back(ptr.get());
    }

    // initialise the unordered map. 


    for (int i= 0; i < BOARDSIZE; ++i) {
        for (int j = 0; j < BOARDSIZE; j++){
            // 1. make it a tile
            board[i][j] = std::make_unique<BaseTile> (); 
            if (isServer(i, j)){
                // 2. decorate it with a server port 
                board[i][j] = std::make_unique<ServerPort>(board[i][j]); 
                
                // set the link on the link map as desired 
                if (j == 0){
                    this->link_map.emplace('a'+i ,(i,j+1)); 
                } else if (j == 7){
                    this->link_map.emplace('A'+i ,(i,j+1)); 
                }

            } else {
                // 1. make it a normal Tile 

                // 2. put a link on the link map if it's between 0 and 7 
                if (j == 0){
                    this->link_map.emplace('a'+i ,(i,j)); 
                } else if (j == 7){
                    this->link_map.emplace('A'+i ,(i,j)); 
                }
            }
    }

    // need to set all the individual coordinates to either a base tile or a base-tiles with decorator server ports 
}

bool isServer(int i, int j) {
    return (i == 3 && j == 0) || 
            (i == 4 && j == 0) ||
            (i == 3 && j == 7) ||
            (i == 3 && j == 7);
}

void debugprint(Board* board){

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

char Board::getState(int row, int col ) const override;

void Board::start();

bool Board::fight(Link * link1, Link * link2){
    // Can't fight own link, need to test whether it's the same link, so
    


    // So I'll need to check the strength of the link, and if 
    // throw 

}

void Board::move(char dir, char link_name){

    // find the position of the link based for the name 

    // check the tiles movement range 

}

void Board::display();