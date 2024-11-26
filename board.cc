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
                // set the link on the link map as desired 
                if (j == 0){
                    board[i][j] = std::make_unique<ServerPort>(0 ,board[i][j], players[0]);
                    this->link_map.emplace('a'+i ,(i,j+1)); 
                } else if (j == 7){
                    board[i][j] = std::make_unique<ServerPort>(1 ,board[i][j], players[1]);
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

// ok so link 1 shall always be the aggressor 
Link* Board::fight(Link * link1, Link * link2){
    // Can't fight own link, need to test whether it's the same link, so
    int x = 0; 
    int y = 0; 
    for (int i = 0; i < BOARDSIZE; ++i){
        for (int j = 0; j < BOARDSIZE; ++j){
                 // find the bloody link
            if (board[i][j]->getLink() == link2){
                board[i][j]->setLink(link1); 
                board[i][j]->activate(); 

                if (board[i][j]->getLink() == nullptr){
                    board[i][j]->setLink(link2);
                    return link2; 
                }
            }  
        }
    }
    auto win = link1->getStrength() <=> link2->getStrength(); 
    if (win >= 0){
        return link1; 
    } 
    return link2; 

}


void check_valid_move(char dir, char link_name){
        // 1. find the position of the link based on the name 
    std::pair op = link_map[link_name]; 
    int move_dist = board[op.first][op.second]->getLink()->getMovement();
    int owner = board[op.first][op.second]->getLink()->getOwner(); 
    std::pair p{0,0}; 
    switch(dir){
        case UP:
            p = std::make_pair(p.first, p.second - move_dist); break; 
        case DOWN:
            p = std::make_pair(p.first, p.second + move_dist); break; 
        case LEFT:
            p = std::make_pair(p.first - move_dist, p.second); break; 
        case RIGHT:
            p = std::make_pair(p.first + move_dist, p.second); break; 
    }

    // 2. check the tiles movement range 
        // To do that I need to know which direction it's allowed to move off the board 
        // so I need to know the owner 
        // Player 1 (0) is at the top so the server ports 
        // Player 2 (1) 
    switch(owner){
        case 0:
            if (p.first < 0 || p.first > 7){
                throw(IllegalMoveException("Player 1 has made an illegal move: exiting the left or right boundaries of the board"));
            } else if (p.second <= 1 && (p.first == 3 || p.first == 4)){
                throw(IllegalMoveException("Player 1 has made an illegal move: going on it's own server port")); 
            } else if (p.second < 0){
                throw(IllegalMoveException("Player 1 has made an illegal move: going back to it's own bay")); 
            }
            break;
        case 1:
            if (p.first < 0 || p.first > 7){
                throw(IllegalMoveException("Player 2 has made an illegal move: exiting the left or right boundaries of the board"));
            } else if (p.second >= 6 && (p.first == 3 || p.first == 4)){
                throw(IllegalMoveException("Player 2 has made an illegal move: going on it's own server port")); 
            } else if (p.second > 7){
                throw(IllegalMoveException("Player 2 has made an illegal move: "));
            }
            break;
    }
}

void Board::move(char dir, char link_name){

    std::pair op = link_map[link_name]; 
    int move_dist = board[op.first][op.second]->getLink()->getMovement();
    int owner = board[op.first][op.second]->getLink()->getOwner(); 
    std::pair p{0,0}; 

    // check if the next move will cause it to download the link (currently will download anything lolololol)
    if (p.first < 0 || p.first > 7){
        download(owner, board[op.first][op.second]->getLink()); 
        update(owner, board[op.first][op.second]->getLink()); 
    }


    // check if the link exists
        // check if it's not a nullptrs
    Link * next = board[op.first][op.second]->getLink(); 

    if (!next && owner == board[op.first][op.second]->getLink()->getOwner()){
        string message = "Player " + (owner + 1);
        message += " has made an illegal move: "; // looks dumb I know but it gets rid of the red squiggly line
        throw(IllegalMoveException(message));
    }

    // so we established that i'ts not out of bounds and that the next link is not one of our own. 
    // 3. check if the there is a link, and fight it 
    // not sure how to check if it's a firewall or a superfireall

    if (next){
        fight(board[p.first][p.second]->getLink(),next); // should update the thing accordingly. 
    }

}

void Board::make_firewall(int i, int j){
    int owner = board[p.first][p.second]->getLink()->getOwner(); 
    board[i][j] = std::make_unique<Firewall>(owner, board[i][j], players[owner]); 
}

void Board::make_super_firewall(int i, int j){
    int owner = board[p.first][p.second]->getLink()->getOwner(); 
    board[i][j] = std::make_unique<SuperFireWall>(owner, board[i][j], players[owner]); 
}

void Board::display(int turn){
    notifyObservers(); 
}