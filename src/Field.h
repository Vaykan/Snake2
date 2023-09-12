#ifndef FIELD_H_
#define FIELD_H_

class Field;
class SnakeHead;
class SnakeBody;
class Cell;
class CellContent;
class Wall;

class Field{
public:
	Field();
	void UIDraw();
	void step();
	bool gameIsPlaying();
	void cellRemove(int x, int y);
	void cellAdd(int x, int y, CellContent *Content);
	void cellMove(int x, int y, CellContent *Moving);
	CellContent *cellGetContent(int x, int y);
	void cellCheckCollision(int x, int y, CellContent *Checker);
	void setGameOver();
private:
	Cell *cell[10][10];
	bool gameOver = false;
	void startFullField();
};

#endif




