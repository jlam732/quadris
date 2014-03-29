#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include "cell.h"
#include "block.h"
#include "gameBoard.h"
#include "iBlock.h"
#define NUM_ROWS 18
#define NUM_COLS 10

using namespace std;

gameBoard::gameBoard() {

	level = 0;
	currentScore = 0;
	hiScore = 0;
	isGraphics = false;
	seed = 0;
	
	//xw = new XWindow();
	//xw = NULL;

	//initialize the board
	board = new Cell **[NUM_ROWS];
	for(int i = 0; i < NUM_ROWS; ++i) {
		board[i] = new Cell * [NUM_COLS];
		for(int j = 0; j < NUM_COLS; j++) {
			board[i][j] = new Cell(i,j);
		}
	}

	//define blocks
	currentBlock = generateBlock();
	nextBlock = generateBlock();

	//Put the current block in the grid
	vector<Cell *> cells = currentBlock->getCells();
	for (vector<Cell *>::iterator it = cells.begin() ; it != cells.end(); ++it) {
		board[(*it)->x][(*it)->y] = *it;
	}
	
}

gameBoard::~gameBoard(){
	for(int i = 0; i < NUM_ROWS; ++i) {
		for(int j = 0; j < NUM_COLS; ++j) {
			delete board[i][j];
		}
		delete board[i];
	}
	delete board;
	
	delete currentBlock;
	delete nextBlock;
	//delete xw;
}

void gameBoard::restart() {
	for(int i = 0; i < NUM_ROWS; ++i) {
		for(int j = 0; j < NUM_COLS; ++j) {
			delete board[i][j];
		}
		delete board[i];
	}
	delete board;
	
	delete currentBlock;
	delete nextBlock;


	board = new Cell **[NUM_ROWS];
	for(int i = 0; i < NUM_ROWS; ++i) {
		board[i] = new Cell * [NUM_COLS];
		for(int j = 0; j < NUM_COLS; j++) {
			board[i][j] = new Cell(i,j);
		}
	}

	//define blocks, but we need to get new ones ASAP
	currentBlock = NULL;
	nextBlock = NULL;
}

Block * gameBoard::generateBlock() {
	switch(level) {
		case 0:
			//read the next one from file...do we need a counter in the meantime
			return new iBlock(this);
			break;
		case 1: {
			int i = rand() % 12;
			switch(i) {
				case 0:
					//return new sBlock(this);
					break;
				case 1:
					//return new zBlock(this);
					break;
				default:
					int j = rand() % 5;
					if(j == 0) { return new iBlock(this); }
					// if(j == 1) { return new jBlock(this); }
					// if(j == 2) { return new lBlock(this); }
					// if(j == 3) { return new oBlock(this); }
					// if(j == 4) { return new tBlock(this); }
				break;
			}
			break;
		}
		case 2: {
			int i = rand() % 7;
			// if(i == 0) { return new iBlock(this); }
			// if(i == 1) { return new jBlock(this); }
			// if(i == 2) { return new lBlock(this); }
			// if(i == 3) { return new oBlock(this); }
			// if(i == 4) { return new sBlock(this); }
			// if(i == 5) { return new zBlock(this); }
			// if(i == 6) { return new tBlock(this); }
			break;
		}
		case 3: {
			int i = rand() % 9;
			switch(i) {
				case 0: case 1:
					//return new sBlock(this);
					break;
				case 2: case 3:
					//return new zBlock(this);
					break;
				default:
					int j = rand() % 5;
					if(j == 0) { return new iBlock(this); }
					// if(j == 1) { return new jBlock(this); }
					// if(j == 2) { return new lBlock(this); }
					// if(j == 3) { return new oBlock(this); }
					// if(j == 4) { return new tBlock(this); }
					break;
			}
			break;
		}
	}
	return NULL;
}

void gameBoard::setSeed(int pSeed) {
	seed = pSeed;
}

void gameBoard::setGraphics() {
	isGraphics = true;
}

bool gameBoard::getGraphics() {
	return isGraphics;
}

void gameBoard::setLevel(int pLevel) {
	level = pLevel;
}

void gameBoard::setLevelZeroFile(std::istream * pFile) {
	file = pFile;
}

void gameBoard::calculateScore() {

}

void gameBoard::remove(int row) {

}

// bool gameBoard::isLegal(int pPostion[]) {	
// 	return true;		
// }

void gameBoard::levelUp() {
	level == 3 ? level = 3 : level++;
}

void gameBoard::levelDown() {
	level == 0 ? level = 0 : level--;
}

void gameBoard::preMove() {
	vector<Cell *> cells = currentBlock->getCells();
	for (vector<Cell *>::iterator it = cells.begin() ; it != cells.end(); ++it) {
		board[(*it)->x][(*it)->y] = new Cell((*it)->x,(*it)->y);
	}
}

void gameBoard::postMove() {
	vector<Cell *> cells = currentBlock->getCells();
	for (vector<Cell *>::iterator it = cells.begin() ; it != cells.end(); ++it) {
		board[(*it)->x][(*it)->y] = *it;
	}
}

void gameBoard::left() {
	
}

void gameBoard::right() {
}

void gameBoard::down() {
}

void gameBoard::drop() {
}

void gameBoard::rotateCW() {
	this->preMove();
	currentBlock->rotateCW();
	this->postMove();
}

void gameBoard::rotateCCW() {

}

ostream &operator<<(ostream &out, const gameBoard &b) {
	//display header
	out << "Level:    " << b.level << endl;
	out << "Score:    " << b.currentScore << endl;
	out << "Hi Score: " << b.hiScore << endl;
	out << "----------" << endl;

	//display game
	for(int i = 0; i < NUM_ROWS; ++i) {
		for(int j = 0; j < NUM_COLS; ++j) {
			out << *(b.board[i][j]);
		}
		out << endl;
	}
	out << "----------" << endl;
	
	//display next block
	out << "Next:" << endl;
	out << *(b.nextBlock);	
	return out;
}
