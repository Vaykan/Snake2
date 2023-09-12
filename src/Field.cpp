#include <iostream>
#include <typeinfo>

#include "Field.h"

#include "SpawnController.h"
#include "CellAndCellContent.h"

using namespace std;
Field::Field(){
	for(int x = 0; x < 10; x++){
		for(int y = 0; y < 10; y++){
			cell[x][y] = new Cell;
		}
	}
	startFullField();
}

void Field::startFullField(){
	for(int x = 0; x < 10; x++){
		for(int y = 0; y < 10; y++){
			cell[x][y]->cont = nullptr;
			}
		}
	for(int x = 0; x < 10; x++){
		SpawnController::getSpawnController().spawnWall(x, 0, this);
		SpawnController::getSpawnController().spawnWall(x, 9, this);
		}
	for(int y = 1; y < 9; y++){
		SpawnController::getSpawnController().spawnWall(0, y, this);
		SpawnController::getSpawnController().spawnWall(9, y, this);
	}
//	cell[4][4]->cont = new SnakeHead(4, 4, this);
	SpawnController::getSpawnController().spawnSnakeHead(4, 4, this);
	SpawnController::getSpawnController().spawnRandomFood(this);
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

//void Field::spawnBody(int x, int y, CellContent *SnakeHead){
//	cell[x][y]->cont = new SnakeBody(SnakeHead);
//}

void Field::setGameOver(){
	gameOver = true;
}

void Field::cellRemove(int x, int y){
	this->cell[x][y]->cont = nullptr;
}

void Field::cellAdd(int x, int y, CellContent *Content){
	this->cell[x][y]->cont = Content;
}

void Field::cellMove(int x, int y, CellContent *Moving){
	if(this->cell[x][y]->cont)
		this->cellCheckCollision(x, y, Moving);
	this->cellAdd(x, y, Moving);
}

CellContent *Field::cellGetContent(int x, int y){
	return this->cell[x][y]->cont;
}

void Field::cellCheckCollision(int x, int y, CellContent *Checker){
	this->cell[x][y]->cont->collision(Checker, this);
}



