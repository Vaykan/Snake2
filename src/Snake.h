#ifndef SNAKE_H_
#define SNAKE_H_

#include "InputScanner.h"
#include "CellAndCellContent.h"
#include "Field.h"

class CellContent;
class SnakeBody;

class SnakeHead : public CellContent{
private:
	SnakeBody *ptrNextBodyPart = nullptr;
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
	virtual void move(Field *fill);
	SnakeBody* getPtrNextBodyPart();
	int getTailLastPositionX();
	int getTailLastPositionY();
	void setTailLastPositionXY(int x, int y);
	void setTail(SnakeBody *newTail);
	void setPtrNextBodyPart(SnakeBody *ptrNextBodyPart);
	SnakeBody* getPtrTail();
protected:

};

class SnakeBody : public CellContent{
private:
	virtual void draw();
	int x, y;
public:
	virtual void collision(CellContent *faced, Field *fill);
	SnakeBody(SnakeHead *ptrSnakeHead);
	void SnakeBodyMove(int x, int y, Field *fill, SnakeHead *snakeHead);
	int getX();
	int getY();
	SnakeBody *ptrNextBodyPart = nullptr;
};




#endif
