#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <fstream>
#include "cell.h"
#include "block.h"
#include "gameBoard.h"
#include "iBlock.h"
#include "jBlock.h"
#include "oBlock.h"
#include "sBlock.h"
#include "zBlock.h"
#include "lBlock.h"
#include "tBlock.h"

using namespace std;

gameBoard::gameBoard() {

	level = 0;
	levelZeroCount = 1;
	currentScore = 0;
	hiScore = 0;
	isGraphics = false;
	srand(0);
	fileName = "sequence.txt";
	
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
	this->postMove();
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
		case 0: {
			//read the next one from file...do we need a counter in the meantime
			char blockType;
			ifstream file(fileName.c_str());
			for(int i = 0; i < levelZeroCount; ++i) {
				file >> blockType;
			}
			levelZeroCount++;
			switch(blockType) {
				case 'I': { return new iBlock(this); break; }
				case 'J': { return new jBlock(this); break; }
				case 'O': { return new oBlock(this); break; }
				case 'S': { return new sBlock(this); break; }
				case 'Z': { return new zBlock(this); break; }
				case 'L': { return new lBlock(this); break; }
				case 'T': { return new tBlock(this); break; }
			}
			break;
		}
		case 1: {
			int i = rand() % 12;
			switch(i) {
				case 0:
					return new sBlock(this);
					break;
				case 1:
					return new zBlock(this);
					break;
				default:
					int j = rand() % 5;
					if(j == 0) { return new iBlock(this); }
					if(j == 1) { return new jBlock(this); }
					if(j == 2) { return new lBlock(this); }
					if(j == 3) { return new oBlock(this); }
					if(j == 4) { return new tBlock(this); }
				break;
			}
			break;
		}
		case 2: {
			int i = rand() % 7;
			if(i == 0) { return new iBlock(this); }
			if(i == 1) { return new jBlock(this); }
			if(i == 2) { return new lBlock(this); }
			if(i == 3) { return new oBlock(this); }
			if(i == 4) { return new sBlock(this); }
			if(i == 5) { return new zBlock(this); }
			if(i == 6) { return new tBlock(this); }
			break;
		}
		case 3: {
			int i = rand() % 9;
			switch(i) {
				case 0: case 1:
					return new sBlock(this);
					break;
				case 2: case 3:
					return new zBlock(this);
					break;
				default:
					int j = rand() % 5;
					if(j == 0) { return new iBlock(this); }
					if(j == 1) { return new jBlock(this); }
					if(j == 2) { return new lBlock(this); }
					if(j == 3) { return new oBlock(this); }
					if(j == 4) { return new tBlock(this); }
					break;
			}
			break;
		}
	}
	return NULL;
}

void gameBoard::setSeed(int pSeed) {
	srand(pSeed);
}

void gameBoard::setGraphics() {
	isGraphics = true;
}

bool gameBoard::getGraphics() {
	return isGraphics;
}

void gameBoard::setFileName(string pFileName) {
	fileName = pFileName;
}

void gameBoard::setLevel(int pLevel) {
	level = pLevel;
}

int gameBoard::getLevel() {
	return level;
}

void gameBoard::calculateScore() {
	int numLinesCleared = 0;
	for(int i = 0; i < NUM_ROWS-3; ++i) {
		bool fullLine = true;
		for(int j = 0; j < NUM_COLS && fullLine; ++j) {
			if(getCell(i,j)->block_type == ' ') {
				fullLine = false;
			}
		}
		if(fullLine) {
			//go through each cell in the line and see if any neighbouring cells have the same unique ID
			//if so, no points for block clear
			for(int j = 0; j < NUM_COLS; ++j) {
				if(checkNeighbourId(i,j)) {
					currentScore += (getCell(i,j)->levelCreated + 1)^2;
				}
			}
			remove(i);
			numLinesCleared++;
		}
	}
	currentScore += (level+numLinesCleared)^2;
}

bool gameBoard::checkNeighbourId(int x, int y) {
	int id = getCell(x,y)->block_id;
	if(x+1 < NUM_ROWS-3) {
		if(getCell(x+1,y)->block_id == id) return false;
	}
	if(x-1 >= 0) {
		if(getCell(x-1,y)->block_id == id) return false;
	}
	if(y+1 < NUM_COLS) {
		if(getCell(x,y+1)->block_id == id) return false;
	}
	if(y-1 >= 0) {
		if(getCell(x,y-1)->block_id == id) return false;
	}
	return true;
}

void gameBoard::remove(int row) {

}

Cell * gameBoard::getCell(int x, int y) {
	return board[x][y];
}

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
		cout << "X/Y: " << (*it)->x << " " << (*it)->y << endl;
		board[(*it)->x][(*it)->y] = *it;
	}
}

void gameBoard::left() {
	this->preMove();
	if(currentBlock->isLegalMove(0,-1)) {
		currentBlock->left();
	}
	this->postMove();
}

void gameBoard::right() {
	this->preMove();
	if(currentBlock->isLegalMove(0,1)) {
		currentBlock->right();
	}
	this->postMove();
}

void gameBoard::down() {
	this->preMove();
	if(currentBlock->isLegalMove(1,0)) {
		currentBlock->down();
	}
	this->postMove();
}

void gameBoard::drop() {
	this->preMove();
	int c = -1;
	bool legal;
	do {
		c++;
		legal = currentBlock->isLegalMove(c,0);
	} while(legal);
	for(int i = 0; i < (c-1); ++i) {
		currentBlock->down();
	}
	this->postMove();

	//point to a new block
	delete currentBlock;
	currentBlock = nextBlock;
	this->postMove();
	nextBlock = generateBlock();
}

void gameBoard::rotateCW() {
	this->preMove();
	currentBlock->rotateCW();
	this->postMove();
}

void gameBoard::rotateCCW() {
	this->preMove();
	currentBlock->rotateCCW();
	this->postMove();
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