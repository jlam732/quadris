#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "block.h"
#include "gameBoard.h"

using namespace std;

Block::Block(gameBoard * pBoard) {
		board = pBoard;
        current_level = pBoard->getLevel();
        current_block_id = 0;
}

Block::~Block(){}

void Block::setLevel(int level){
	current_level = level;
}

vector<Cell *> Block::getCells() {
	return cells;
}

char Block::getBlockType() {
	return block_type;
}

bool Block::isLegalMove(int pX, int pY) {
	for(int i = 0; i < 4; ++i) {
		int tmpX = cells.at(i)->x+pX;
		int tmpY = cells.at(i)->y+pY;
		if(!isLegalXY(tmpX,tmpY)) {
			cout << "it is not legal" << endl;
			return false;
		}
	}
	cout << "it is legal" << endl;
	return true;
}

bool Block::isLegalXY(int x, int y) {
	if(x < 0 || x > (NUM_ROWS-1) || y < 0 || y > (NUM_COLS-1) || board->getCell(x,y)->filled){ 
		return false;
	}
	return true;
}

ostream &operator<<(ostream &out, const Block &bl) {
	int c = 0;
	stringstream ss;
	for(int i = 0; i < 4 && c < 4; ++i) {
		for(int j = 0; j < 4 && c < 4; ++j) {
			if(bl.cells.at(c)->x == i && bl.cells.at(c)->y == j) {
				ss << *bl.cells.at(c);
				c++;
			} else {
				ss << ' ';
			}
		}
		if(ss.str().find_first_not_of(' ') != std::string::npos) {
			out << ss.str() << endl;
		}
		ss.str("");
	}
	return out;
}