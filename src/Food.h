#ifndef FOOD_H_
#define FOOD_H_

#include "CellAndCellContent.h"

class Food : public CellContent{
public:
	Food(int x, int y);
private:
	virtual void draw();
	virtual void collision(CellContent *faced, Field *fill);
	virtual void move(Field *fill);
	int mX, mY;
};

#endif
