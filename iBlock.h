#ifndef __IBLOCK_H__
#define __IBLOCK_H__
#include "block.h"

class iBlock : public Block {

 public:
  iBlock();
  ~iBlock();
  virtual void rotateCCW();
  virtual void rotateCW();
  virtual void left();
  virtual void right();
  virtual void down();
	
};
#endif
