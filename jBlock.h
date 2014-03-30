#ifndef __JBLOCK_H__
#define __JBLOCK_H__
#include "block.h"

class jBlock : public Block {

 public:
  jBlock(gameBoard * pBoard);
  ~jBlock();
  virtual void rotateCCW();
  virtual void rotateCW();
  virtual void left();
  virtual void right();
  virtual void down();
  virtual bool isLegalRotate(int pDirection); //0 - clockwise, 1 - counterclockwise	
};
#endif
