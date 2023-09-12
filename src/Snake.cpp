#include <iostream>

#include "Snake.h"

using namespace std;

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
		ptrNextBodyPart->SnakeBodyMove(x, y, fill, this);
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
	x = ptrSnakeHead->getTailLastPositionX();
	y = ptrSnakeHead->getTailLastPositionY();

	if(ptrSnakeHead->getPtrTail())
		ptrSnakeHead->getPtrTail()->ptrNextBodyPart = this;
	 else
		ptrSnakeHead->setPtrNextBodyPart(this);
	ptrSnakeHead->setTail(this);
}

void SnakeBody::collision(CellContent *faced, Field *fill){
	if(typeid(*faced) == typeid(SnakeHead)){
		fill->setGameOver();
	}
}

void SnakeBody::draw(){
	cout << "%";
}
void SnakeBody::SnakeBodyMove(int x, int y, Field *fill, SnakeHead *snakeHead){
	fill->cellRemove(this->x, this->y);
	fill->cellAdd(x, y, this);
	if(ptrNextBodyPart){
		ptrNextBodyPart->SnakeBodyMove(this->x, this->y, fill, snakeHead);
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
