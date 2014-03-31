#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "cell.h"
#include <vector>

class gameBoard;

class Block {

 public:
  Block(gameBoard * pBoard);
  ~Block();
  void setLevel(int);
  std::vector<Cell *> getCells();
  char getBlockType();
  virtual void rotateCCW()= 0;
  virtual void rotateCW()= 0;
  virtual void left() = 0;
  virtual void right() = 0;
  virtual void down() = 0;
  friend std::ostream &operator<<(std::ostream &out, const Block &bl);
  bool isLegalMove(int pX, int pY);
  bool isLegalXY(int x, int y);
 protected:
  gameBoard * board;
  std::vector<Cell *> cells;
  int current_block_id;
  char block_type;
  int current_level;

};

#endif
