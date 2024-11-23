#ifndef STUDIO_H
#define STUDIO_H
#include <iostream>
#include "subject.h"
#include <vector>
#include "player.h"
#include "gamecontroller.h"
#include "tile.h"
#include "link.h"
#include <unordered_map>
#include ""

// do I need to potentially forward declare anything?  class AsciiArt;

class Board: public Subject{
  
  std::vector<Player * > players; 
  Tile * board[BOARDSIZE][BOARDSIZE]; 
  unordered_map 
  GameController* gc; // SYNTAX is porb wrong here 

 public:
  explicit Board(const std::vector<std::unique_ptr<Player>> &players, GameController* gc);

  char getState(int row, int col ) const override;

  void start();
  void fight(Link * link1, Link * link2); 
  void move(char dir, char link_name); 

#endif