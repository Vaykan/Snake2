#include <iostream>

#include "Wall.h"

#include "Field.h"
#include "Snake.h"

using namespace std;

void Wall::draw(){
	cout << "#";
}

void Wall::collision(CellContent *faced, Field *fill){
	if(typeid(*faced) == typeid(SnakeHead)){
		fill->setGameOver();
	}
}
