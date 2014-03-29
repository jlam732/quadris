#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "cell.h"
#include <vector>

class Block {

  int current_level;
 public:
  Block();
  ~Block();
  void left();
  void right();
  void down();
  void setLevel(int);
  //virtual vector<int,int> getPosition() = 0;
  virtual void rotateCCW()= 0;
  virtual void rotateCW()= 0;
  friend std::ostream &operator<<(std::ostream &out, const Block &bl);
 protected:
  Cell **cells;
  int current_block_id;
  char block_type;


};
#endif
