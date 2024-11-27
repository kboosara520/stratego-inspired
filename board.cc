#include "board.h"
//[i][j]
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


Board::Board(const std::vector<std::unique_ptr<Player>> &players, const int &turn): turn{turn} {
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
                    board[i][j] = std::make_unique<ServerPort>(0 , std::move(board[i][j]), this->players);
                    this->link_map.emplace('a'+i , std::pair<int, int>{i,j+1}); 
                } else if (j == 7){
                    board[i][j] = std::make_unique<ServerPort>(1 , std::move(board[i][j]), this->players);
                    this->link_map.emplace('A'+i , std::pair<int, int>{i,j - 1}); 
                }
            } else {
                // 2. put a link on the link map if it's between 0 and 7 
                if (j == 0){
                    this->link_map.emplace('a'+i ,std::pair<int, int>{i, j}); 
                } else if (j == 7){
                    this->link_map.emplace('A'+i ,std::pair<int, int>{i, j}); 
                }
            }
        }
    }
    for (auto &player: players) {
        for (auto &link: player->getLinks()) {
            std::pair<int, int> coords = link_map[link.first];
            board[coords.first][coords.second]->setLink(link.second.get());
        }
    }
}

bool Board::isServer(int i, int j) {
    return (i == 3 && j == 0) || 
            (i == 4 && j == 0) ||
            (i == 3 && j == 7) ||
            (i == 4 && j == 7);
}


void Board::debugprint(Board* board){
    for (int i = 0; i < BOARDSIZE; ++i) {
        for (int j = 0; j < BOARDSIZE; j++){
            bool tel = true;
            for (auto it = link_map.begin(); it != link_map.end(); ++it){ 
                if (it->second == std::make_pair(i, j)) {
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


char Board::getState(int row, int col ) const{
    return board[row][col]->charAt(); 
}

// ok so link 1 shall always be the aggressor 
Link* Board::fight(Link * link1, Link * link2){
    // Can't fight own link, need to test whether it's the same link, so
    // for (int i = 0; i < BOARDSIZE; ++i){
    //     for (int j = 0; j < BOARDSIZE; ++j){
    //              // find the bloody link
    //         if (board[i][j]->getLink() == link2){
    //             board[i][j]->setLink(link1); 
    //             board[i][j]->activate(); 

    //             if (board[i][j]->getLink() == nullptr){
    //                 board[i][j]->setLink(link2);
    //                 return link2; 
    //             }
    //         }  
    //     }
    // }
    auto win = link1->getStrength() <=> link2->getStrength(); 
    if (win == 0 || win > 0){
        return link1; 
    } 
    return link2; 
}


void Board::check_valid_move(char dir, char link_name){
        // 1. find the position of the link based on the name 
    std::pair op {0,0}; 
    op = link_map[link_name]; 
    int move_dist = board[op.first][op.second]->getLink()->getMovement();
    std::pair p{0,0}; 
    switch(dir){
        case UP:
            p = std::make_pair(op.first, op.second - move_dist); break; 
        case DOWN:
            p = std::make_pair(op.first, op.second + move_dist); break; 
        case LEFT:
            p = std::make_pair(op.first - move_dist, op.second); break; 
        case RIGHT:
            p = std::make_pair(op.first + move_dist, op.second); break; 
    }

    // 2. check the tiles movement range 
        // To do that I need to know which direction it's allowed to move off the board 
        // so I need to know the owner 
        // Player 1 (0) is at the top so the server ports 
        // Player 2 (1) 
    switch(turn){
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
                throw(IllegalMoveException("Player 2 has made an illegal move: going back to it's own bay"));
            }
            break;
    }
}

void Board::move(char dir, char link_name){

    std::pair op {0,0};
    op = link_map[link_name]; 
    int move_dist = board[op.first][op.second]->getLink()->getMovement();
    std::pair p{0,0}; 
    switch(dir){
        case UP:
            p = std::make_pair(op.first, op.second - move_dist); break; 
        case DOWN:
            p = std::make_pair(op.first, op.second + move_dist); break; 
        case LEFT:
            p = std::make_pair(op.first - move_dist, op.second); break; 
        case RIGHT:
            p = std::make_pair(op.first + move_dist, op.second); break; 
    }
    check_valid_move(dir, link_name); 

    // check if the next move will cause it to download the link (currently will download anything lolololol)
    if (p.second < 0 || p.second > 7){
        download(turn, link_name); 
        return;
    }


    // check if the link exists
        // check if it's not a nullptrs
    Link * next = board[p.first][p.second]->getLink();
    if (!next) {
        Link *link = board[op.first][op.second]->getLink();
        board[op.first][op.second]->setLink(nullptr);
        board[p.first][p.second]->setLink(link);
        link_map[link_name] = p;
        board[p.first][p.second]->activate();
    }

    else if (turn == board[p.first][p.second]->getLink()->getOwner()){
        std::cout << "this condition" << std::endl;
        int index = turn + 1;
        std::string message = "Player " + std::to_string(index) + " has made an illegal move";
        throw IllegalMoveException{message};
    }

    // so we established that i'ts not out of bounds and that the next link is not one of our own. 
    // 3. check if the there is a link, and fight it 
    // not sure how to check if it's a firewall or a superfireall

    else {
        Link *first = board[op.first][op.second]->getLink();
        Link *second = next;
        Link *winner = fight(first, second); // should update the thing accordingly. 
        if (winner == first) {
            download(first->getOwner(), second->getName());
            board[op.first][op.second]->setLink(nullptr);
            board[p.first][p.second]->setLink(winner);
            link_map[link_name] = p;    
            board[p.first][p.second]->activate();
            if (first->getIsAndOne()) {
                throw IllegalMoveException{std::string(1, first->getName())};
            }
        }
        else download(second->getOwner(), first->getName());
    }
}

void Board::download(int player, char linkname) {
    // check that 
    if (link_map.count(linkname) <= 0) {
        throw IllegalAbilityUseException{"Illegal ability use!: Link does not exist"};
    }
    std::pair<int, int> coords = link_map[linkname];
    Tile *tile = board[coords.first][coords.second].get();
    Link *link = tile->getLink();
    if (link->getIsDead()) {
        throw IllegalAbilityUseException{"Illegal ability use!: Link is dead!"};
    }
    char type = link->getType();
    if (type == VIRUS) players[player]->setVirus(players[player]->getVirus() + 1);
    else players[player]->setData(players[player]->getData() + 1);
    tile->setLink(nullptr);
}

void Board::scan(char linkname) {
    if (link_map.count(linkname) <= 0) {
        throw IllegalAbilityUseException{"Illegal ability use!: Link does not exist"};
    }
    std::pair<int, int> coords = link_map[linkname];
    Tile *tile = board[coords.first][coords.second].get();
    Link *link = tile->getLink();
    if (link->getIsDead()) {
        throw IllegalAbilityUseException{"Illegal ability use!: Link is dead!"};
    }
    link->setIsVisble(true);
}


void Board::polarize(char linkname) {
    // check 
    if (!link_map.count(linkname)){
        throw(IllegalAbilityUseException("Illegal ability use!: Link does not exist")); 
    }
    std::pair<int, int> p = link_map.at(linkname); 
    // check if it's dead
    if (board[p.first][p.second]->getLink()){
        throw(IllegalAbilityUseException("Illegal ability use!: Link is dead!"));
    }
    //check if it's alive and it exists 
    board[p.first][p.second]->getLink()->polarize(); 
}


void Board::make_firewall(int i, int j){

    // checks if it's null
    if (board[i][j]->getLink() || (board[i][j]->charAt() == SERVERPORTNAME) ||
     board[i][j]->charAt() == FIREWALLNAMES[0] ||
      board[i][j]->charAt() == FIREWALLNAMES[1]) {
        throw(IllegalAbilityUseException("Illegal ability use!: Firewall")); 
    }
    
    board[i][j] = std::make_unique<Firewall>(turn, std::move(board[i][j]), players);
}

void Board::make_super_firewall(int i, int j){
    char symbol = board[i][j]->charAt();
    if ((symbol == SERVERPORTNAME && ((turn == 0 && j != 0) || (turn == 1 && j != 7))) ||
        symbol == FIREWALLNAMES[(turn + 1) % 2] ||
        symbol == '.' || board[i][j]->getLink()){
        throw(IllegalAbilityUseException("Illegal ability use!: Not a serverport or Firewall belonging to the player")); 
    }
 
    board[i][j] = std::make_unique<SuperFireWall>(turn, std::move(board[i][j]), players); 
}

void Board::display(int turn){
    notifyObservers(turn); 
}
