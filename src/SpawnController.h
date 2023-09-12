#ifndef SRC_SPAWNCONTROLLER_H_
#define SRC_SPAWNCONTROLLER_H_

#include "Field.h"

class SpawnController{
public:
	static SpawnController getSpawnController();
	void spawnSnakeHead(int x, int y, Field *fill);
	void spawnSnakeBody(int x, int y, SnakeHead *snakeHead, Field *fill);
	void spawnWall(int x, int y, Field *fill);
	void spawnFood(int x, int y, Field *fill);
	void spawnRandomFood(Field *fill);

private:
	SpawnController();
	static SpawnController *storage;
};

#endif
