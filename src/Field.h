#ifndef FIELD_H_
#define FIELD_H_
#include "InputScanner.h"

class Field;
class SnakeHead;
class Alive;

class CellContent{
public:
	virtual ~CellContent();
	virtual void draw();
	virtual void collision(Alive *faced, Field *fill);
};

class Cell{
public:
	CellContent *cont;
};

class Field{
public:
	Field();
	void UIDraw();
	void step();
	bool gameIsPlaying();
	void cellRemove(int x, int y);
	void cellAdd(int x, int y, CellContent *Content);
	void cellMove(int x, int y, Alive *Moving);
	CellContent *cellGetContent(int x, int y);
	void cellCheckCollision(int x, int y, Alive *Checker);
	void spawnFood();
	void spawnBody(int x, int y, Alive* SnakeHead);
	SnakeHead* getPtrSnakeHead();
	void setGameOver();
private:
	SnakeHead *ptrSnakeHead;
	Cell *cell[10][10];
	bool gameOver;
	void startFullField();
};

class Alive : public CellContent{

};

class Not_alive : public CellContent{

};



class SnakeBody : public Alive{
private:
	virtual void draw();
	int x, y;
public:
	virtual void collision(Alive *faced, Field *fill);
	SnakeBody(SnakeHead *ptrSnakeHead);
	void move(int x, int y, Field *fill, SnakeHead *snakeHead);
	int getX();
	int getY();
	SnakeBody *ptrNextBodyPart;
};

class SnakeHead : public Alive{
private:
	SnakeBody *ptrNextBodyPart;
	SnakeBody *ptrTail;
	int x, y;
	int tailLastPositionX, tailLastPositionY;
	void draw();
	void switchDir(int &x, int &y, direction &dir);
	bool isNeck(Field *fill, int neckX, int neckY);
	direction dir;
public:
	SnakeHead(int x, int y, Field *fill);
	int tempX;
	int tempY;
	void move(Field *fill);
	SnakeBody* getPtrNextBodyPart();
	int getTailLastPositionX();
	int getTailLastPositionY();
	void setTailLastPositionXY(int x, int y);
	void setTail(SnakeBody *newTail);
	void setPtrNextBodyPart(SnakeBody *ptrNextBodyPart);
	SnakeBody* getPtrTail();
protected:

};

class Food : public Not_alive{
private:
	virtual void draw();
	virtual void collision(Alive *faced, Field *fill);
};

class Wall : public Not_alive{
	virtual void draw();
	virtual void collision(Alive *faced, Field *fill);
};
#endif
