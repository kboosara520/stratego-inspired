#include "board.h"
#include "constants.h"

Board::Board(const std::vector<std::unique_ptr<Player>> &players, GameController *gc): gc{gc} {
    for (auto &ptr: players) {
        this->players.emplace_back(ptr.get());
    }
}

char Board::getState(int row, int col ) const override;

void Board::start();

void Board::fight(Link * link1, Link * link2); 

void Board::move(char dir, char link_name); 

void Board::display();