#ifndef FIELD_H_
#define FIELD_H_


class Field;
class SnakeHead;
class SnakeBody;

class CellContent{
public:
	virtual ~CellContent();
	virtual void draw();
	virtual void collision(CellContent *faced, Field *fill);
	virtual void move(Field *fill);
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
	void cellMove(int x, int y, CellContent *Moving);
	CellContent *cellGetContent(int x, int y);
	void cellCheckCollision(int x, int y, CellContent *Checker);
	void spawnFood();
	void spawnBody(int x, int y, CellContent* SnakeHead);
	void setGameOver();
private:
	Cell *cell[10][10];
	bool gameOver;
	void startFullField();
};



class Food : public CellContent{
private:
	virtual void draw();
	virtual void collision(CellContent *faced, Field *fill);
};

class Wall : public CellContent{
	virtual void draw();
	virtual void collision(CellContent *faced, Field *fill);
};
#endif
