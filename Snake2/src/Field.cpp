#include <iostream>
#include <typeinfo>
#include "Field.h"
#include "Util.h"

using namespace std;
Field::Field(){
	for(int x = 0; x < 10; x++){
		for(int y = 0; y < 10; y++){
			cell[x][y] = new Cell;
		}
	}
	startFullField();
	gameOver = false;
}

void Field::startFullField(){
	for(int x = 0; x < 10; x++){
		for(int y = 0; y < 10; y++){
			cell[x][y]->cont = nullptr;
			}
		}
	for(int x = 0; x < 10; x++){
		cell[x][0]->cont = new Wall;
		cell[x][9]->cont = new Wall;
		}
	for(int y = 1; y < 9; y++){
		cell[0][y]->cont = new Wall;
		cell[9][y]->cont = new Wall;
	}
	cell[4][4]->cont = new SnakeHead(4, 4, this);
	int x, y;
	while(true){
		x = getRandNumInt();
		y = getRandNumInt();
		if(!cell[x][y]->cont)
			cell[x][y]->cont = new Food;
	}
}

void Field::step(){
	for(int x = 0; x < 10; x++){
		for(int y = 0; y < 10; y++){
			if(cell[x][y])
				cell[x][y]->cont->move(this);
		}
	}
}

bool Field::gameIsPlaying(){
	return !gameOver;
}

void Field::UIDraw(){
	system("cls");
	for(int y = 0; y < 10; y++){
		for(int x = 0; x < 10; x++){
			if(cell[x][y]->cont)
				cell[x][y]->cont->draw();
			else
				cout << " ";
		}
		cout << endl;
	}
}

void Field::spawnBody(int x, int y, CellContent *SnakeHead){
	cell[x][y]->cont = new SnakeBody(SnakeHead);
}

void Field::setGameOver(){
	gameOver = true;
}

void Field::cellRemove(int x, int y){
	this->cell[x][y]->cont = nullptr;
}

void Field::cellAdd(int x, int y, CellContent *Content){
	this->cell[x][y]->cont = Content;
}

void Field::cellMove(int x, int y, Alive *Moving){
	if(this->cell[x][y]->cont)
		this->cellCheckCollision(x, y, Moving);
	this->cellAdd(x, y, Moving);
}

CellContent *Field::cellGetContent(int x, int y){
	return this->cell[x][y]->cont;
}

void Field::cellCheckCollision(int x, int y, Alive *Checker){
	this->cell[x][y]->cont->collision(Checker, this);
}



CellContent::~CellContent() {}
void CellContent::draw(){}
void CellContent::collision(Alive *faced, Field *fill){}

void Wall::draw(){
	cout << "#";
}

void Wall::collision(Alive *faced, Field *fill){
	if(typeid(*faced) == typeid(SnakeHead)){
		fill->setGameOver();
	}
}



void Food::draw(){
	cout << "+";
}
void Food::collision(Alive *faced, Field *fill){
	if(typeid(*faced) == typeid(SnakeHead)){
		fill->spawnBody(fill->getPtrSnakeHead()->getTailLastPositionX(), fill->getPtrSnakeHead()->getTailLastPositionY(), faced);
		fill->spawnFood();
		delete this;
	}
}



