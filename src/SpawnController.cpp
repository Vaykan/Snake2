#include "SpawnController.h"

//#include "CellAndCellContent.h"
#include "Util.h"
#include "Snake.h"
#include "Food.h"
#include "Wall.h"

SpawnController::SpawnController(){}

SpawnController* SpawnController::storage = nullptr;
SpawnController SpawnController::getSpawnController(){
	if(!storage)
		storage = new SpawnController;
	return *storage;
}

void SpawnController::spawnSnakeHead(int x, int y, Field *fill){
	SnakeHead *snakeHead = new SnakeHead(x, y, fill);
	fill->cellAdd(x, y, snakeHead);
}

void SpawnController::spawnSnakeBody(int x, int y, SnakeHead *snakeHead, Field *fill){
	SnakeBody *snakeBody = new SnakeBody(snakeHead);
	fill->cellAdd(x, y, snakeBody);
}

void SpawnController::spawnWall(int x, int y, Field *fill){
	Wall *wall = new Wall;
	fill->cellAdd(x, y, wall);
}

void SpawnController::spawnFood(int x, int y, Field *fill){
	Food *food = new Food(x, y);
	fill->cellAdd(x, y, food);
}

void SpawnController::spawnRandomFood(Field *fill){
	bool foodIsSpawn = false;
	while(!foodIsSpawn){
		int x = getRandNumInt();
		int y = getRandNumInt();
		if(!fill->cellGetContent(x, y)){
			Food *food = new Food(x, y);
			fill->cellAdd(x, y, food);
			foodIsSpawn = true;
		}
	}

}
