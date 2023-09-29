#ifndef SRC_NEURALNETWORK_H_
#define SRC_NEURALNETWORK_H_

#include "InputScanner.h"

#include "Field.h"

class Field;

class Neuron{
public:
	void setValue(float inputValue, float weight);
	void activateSigmoid();
	float getValue();
private:
	static float sigmoid(float x);
	float value;
};
class NeuralNetwork {
public:
	NeuralNetwork();
	void saveWeightInFile();
	direction getOutput(Field *fill);
	float getScore();
	void randWeightStorageSmall();
	Neuron *neuron[332];
	float *weightStorage[10752];
private:
//	enum eCellContentType{EMPTY, FOOD, SNAKEHEAD, SNAKEBODY, WALL};
	float typeConversionToFloat(CellContent::eCellContentType type);
	void inputLayer(Field *fill);
	void hiddenLayer1(Field *fill, int &weightNum);
	void hiddenLayer2(Field *fill, int &weightNum);
	void outputLayer(Field *fill, int &weightNum);
	direction getResult();
	float score = 1;
};

#endif
