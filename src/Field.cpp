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
	ptrSnakeHead = new SnakeHead(4, 4, this);
	spawnFood();
	}

void Field::step(){
	ptrSnakeHead->move(this);
	}

bool Field::gameIsPlaying(){
	if(gameOver == true)
		return false;
	return true;
}

void Field::UIDraw(){
	system("cls");
	for(int y = 0; y < 10; y++){
		for(int x = 0; x < 10; x++){
			if (cell[x][y]->cont){
				cell[x][y]->cont->draw();
			}else{
				cout << " ";
			}
		}
		cout << endl;
	}
}
void Field::spawnFood(){
	bool FoodSpawned = false;
	int x, y;
	while(FoodSpawned == false){
		x = getRandNumInt();
		y = getRandNumInt();
		if(!cell[x][y]->cont){
			cell[x][y]->cont = new Food;
			FoodSpawned = true;
		}
	}
}

void Field::spawnBody(int x, int y, Alive* SnakeHead){
	cell[x][y]->cont = new SnakeBody(ptrSnakeHead);
}

SnakeHead* Field::getPtrSnakeHead(){
	return ptrSnakeHead;
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

SnakeHead::SnakeHead(int x, int y, Field *fill){
	fill->cellAdd(x, y, this);
	ptrNextBodyPart = nullptr;
	ptrTail = nullptr;
	dir = STOP;
	this->x = x;
	this->y = y;
	tailLastPositionX = this->x;
	tailLastPositionY = this->y;
	tempX = 4;
	tempY = 4;
}


void SnakeHead::draw(){
	cout << "O";
}

void SnakeHead::setTail(SnakeBody *newTail){
	ptrTail = newTail;
}

SnakeBody* SnakeHead::getPtrTail(){
	return ptrTail;
}
void SnakeHead::move(Field *fill){
	tailLastPositionX = x;
	tailLastPositionY = y;
	int neckX, neckY;
	fill->cellRemove(x, y);

	if(ptrNextBodyPart){
		neckX = ptrNextBodyPart->getX();
		neckY = ptrNextBodyPart->getY();
		ptrNextBodyPart->move(x, y, fill, this);
	}
	direction tempDir = dir;
	tempX = x;
	tempY = y;

	dir = inputDir();
	switchDir(x, y, dir);
	if(!isNeck(fill, neckX, neckY) && dir != STOP){
		fill->cellMove(x, y, this);
	}else{
		dir = tempDir;
		x = tempX;
		y = tempY;
		switchDir(x, y, dir);
		fill->cellMove(x, y, this);
	}
}

SnakeBody* SnakeHead::getPtrNextBodyPart(){
	return ptrNextBodyPart;
}
int SnakeHead::getTailLastPositionX(){
	return tailLastPositionX;
}
int SnakeHead::getTailLastPositionY(){
	return tailLastPositionY;
}
void SnakeHead::setTailLastPositionXY(int x, int y){
	tailLastPositionX = x;
	tailLastPositionY = y;
}
void SnakeHead::setPtrNextBodyPart(SnakeBody *ptrNextBodyPart){
	this->ptrNextBodyPart = ptrNextBodyPart;
}

void SnakeHead::switchDir(int &x, int &y, direction &dir){
	switch(dir){
	case STOP: break;
	case UP: y--;
	break;
	case RIGHT: x++;
	break;
	case DOWN: y++;
	break;
	case LEFT: x--;
	}
}

bool SnakeHead::isNeck(Field *fill, int neckX, int neckY){
	if(!ptrNextBodyPart)
		return false;
	else if(x == neckX && y == neckY)
		return true;
	else
		return false;
}

SnakeBody::SnakeBody(SnakeHead *ptrSnakeHead){
	ptrNextBodyPart = nullptr;
	x = ptrSnakeHead->getTailLastPositionX();
	y = ptrSnakeHead->getTailLastPositionY();

	if(ptrSnakeHead->getPtrTail())
		ptrSnakeHead->getPtrTail()->ptrNextBodyPart = this;
	 else
		ptrSnakeHead->setPtrNextBodyPart(this);
	ptrSnakeHead->setTail(this);
}

void SnakeBody::collision(Alive *faced, Field *fill){
	if(typeid(*faced) == typeid(SnakeHead)){
		fill->setGameOver();
	}
}

void SnakeBody::draw(){
	cout << "%";
}
void SnakeBody::move(int x, int y, Field *fill, SnakeHead *snakeHead){
	fill->cellRemove(this->x, this->y);
	fill->cellAdd(x, y, this);
	if(ptrNextBodyPart){
		ptrNextBodyPart->move(this->x, this->y, fill, snakeHead);
	}else{
		snakeHead->setTailLastPositionXY(this->x, this->y);
		snakeHead->setTail(this);
	}
	this->x = x;
	this->y = y;
}

int SnakeBody::getX(){
	return x;
}
int SnakeBody::getY(){
	return y;
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



