#ifndef SRC_CELLANDCELLCONTENT_H_
#define SRC_CELLANDCELLCONTENT_H_

class Field;

class CellContent{
public:
	virtual ~CellContent();
	virtual void draw();
	virtual void collision(CellContent *faced, Field *fill);
	virtual void move(Field *fill);
};

class Cell{
public:
	CellContent *cont = nullptr;
};

#endif
