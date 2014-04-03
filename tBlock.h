#ifndef __TBLOCK_H__
#define __TBLOCK_H__
#include "block.h"

class tBlock : public Block {

 public:
  tBlock(gameBoard * pBoard, int pId);
  ~tBlock();
  virtual void rotateCCW();
  virtual void rotateCW();
};
#endif
