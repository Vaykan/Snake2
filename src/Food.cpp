#include <iostream>

#include "Food.h"

#include "Snake.h"
#include "SpawnController.h"

using namespace std;

Food::Food(int x, int y){
	mX = x;
	mY = y;
}

void Food::draw(){
	cout << "+";
}

void Food::collision(CellContent *faced, Field *fill){
	if(typeid(*faced) == typeid(SnakeHead)){
		SnakeHead* snakeHead = dynamic_cast<SnakeHead*>(faced);
		SpawnController::getSpawnController().spawnSnakeBody(snakeHead->getTailLastPositionX(),
				snakeHead->getTailLastPositionY(), snakeHead, fill);
		SpawnController::getSpawnController().spawnRandomFood(fill);
		fill->cellRemove(mX, mY);
		delete this;
	}
}

void Food::move(Field *fill){}
