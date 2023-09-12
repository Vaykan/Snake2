#ifndef SRC_WALL_H_
#define SRC_WALL_H_

#include "CellAndCellContent.h"

class Wall : public CellContent{
	virtual void draw();
	virtual void collision(CellContent *faced, Field *fill);
};

#endif
