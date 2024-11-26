#ifndef STUDIO_H
#define STUDIO_H
#include <iostream>
#include <unordered_map>
#include <utility>
#include <memory> 
#include <vector>
#include <compare>
#include "illegalmoveexception.h"
#include "subject.h"
#include "player.h"
#include "tile.h"
#include "link.h"
#include "constants.h"
#include "basetile.h"
#include "serverport.h"
#include "firewall.h"
#include "superfirewall.h"


// do I need to potentially forward declare anything?  


class Board: public Subject{
  const int &turn;
  std::vector<Player *> players; 
  std::unique_ptr<Tile> board[BOARDSIZE][BOARDSIZE]; 
  std::unordered_map< char , std::pair<int, int>> link_map;
  GameController * gc; 

  // my private methods (helper functions)
  bool isServer(int i, int j);
  void debugprint(Board* board); 
  void check_valid_move(char dir, char link_name);

 public:
  explicit Board(const std::vector<std::unique_ptr<Player>> &players, const int &turn);

  char getState(int row, int col ) const override;

  Link * fight(Link * link1, Link * link2); 
  void move(char dir, char link_name); 
  void make_firewall(int i, int j); 
  void make_super_firewall(int i, int j); 
  void display(int turn); // notifyall
  void download(int player, Link * link); 
  void update(int player, Link * link); 
  void apply(char abName, int x, int y);
};

#endif