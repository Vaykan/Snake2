#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

#include "NeuralNetwork.h"

#include "Util.h"
#include "Field.h"

using namespace std;

void Neuron::setValue(float inputValue, float weight){
	value += inputValue * weight;
}

void Neuron::activateSigmoid(){
	value = sigmoid(value);
}

float Neuron::getValue(){
	return value;
}

float Neuron::sigmoid(float x){
	return 1.0 / (1.0 + std::exp(-x));
}

NeuralNetwork::NeuralNetwork(){
	for(int x = 0; x < 332; x++){
		neuron[x] = new Neuron;
	}
	for(int x = 0; x < 10752; x++){
		weightStorage[x] = new float;
		*weightStorage[x] = getRandNumFloatFrom0to1();
	}
}

void NeuralNetwork::saveWeightInFile(){
	ofstream file;
	file.open("Weight.txt");
	string input;
	for(int x = 0; x < 10752; x++){
		input = to_string(*weightStorage[x]);
		file << input << endl;
	}
	file.close();
}

direction NeuralNetwork::getOutput(Field *fill){
	int weightNum = 0;
	inputLayer(fill);
	hiddenLayer1(fill, weightNum);
	hiddenLayer2(fill, weightNum);
	outputLayer(fill, weightNum);
	return getResult();
}

void NeuralNetwork::inputLayer(Field *fill){
	int inputNeuron = 0;
	for(int x = 0; x < 10; x++){
		for(int y = 0; y < 10; y++){
			neuron[inputNeuron]->setValue(typeConversionToFloat(fill->getTypeInCell(x, y)), 1);
			inputNeuron++;
		}
	}
}

void NeuralNetwork::hiddenLayer1(Field *fill, int &weightNum){
	for(int hiddenLayer1 = 100; hiddenLayer1 < 164; hiddenLayer1++){
		for(int inputNeuron = 0; inputNeuron < 100; inputNeuron++){
			neuron[hiddenLayer1]->setValue(neuron[inputNeuron]->getValue(), *weightStorage[weightNum]);
			weightNum++;
		}
		neuron[hiddenLayer1]->activateSigmoid();
	}
}
void NeuralNetwork::hiddenLayer2(Field *fill, int &weightNum){
	for(int hiddenLayer2 = 164; hiddenLayer2 < 328; hiddenLayer2++){
		for(int hiddenLayer1 = 100; hiddenLayer1 < 164; hiddenLayer1++){
			neuron[hiddenLayer2]->setValue(neuron[hiddenLayer1]->getValue(), *weightStorage[weightNum]);
			weightNum++;
		}
		neuron[hiddenLayer2]->activateSigmoid();
	}
}

void NeuralNetwork::outputLayer(Field *fill, int &weightNum){
	for(int outputLayer = 328; outputLayer < 332; outputLayer++){
		for(int hiddenLayer2 = 164; hiddenLayer2 < 328; hiddenLayer2++){
			neuron[outputLayer]->setValue(neuron[hiddenLayer2]->getValue(), *weightStorage[weightNum]);
			weightNum++;
		}
		neuron[outputLayer]->activateSigmoid();
		if(neuron[outputLayer]->getValue() >= 0.5f)
			neuron[outputLayer]->setValue(1, 1);
		else
			neuron[outputLayer]->setValue(0, 1);
	}
}

direction NeuralNetwork::getResult(){
	if(neuron[328]->getValue())
		return UP;
	if(neuron[329]->getValue())
		return DOWN;
	if(neuron[330]->getValue())
		return LEFT;
	if(neuron[331]->getValue())
		return RIGHT;
	return STOP;
}

float NeuralNetwork::getScore(){
	return score;
}

void NeuralNetwork::randWeightStorageSmall(){
	for(int x = 0; x < 10752; x++){
		*weightStorage[x] += getRandNumFloatSmall();
		if(*weightStorage[x] < 0)
			weightStorage[x] = 0;
	}
}

float NeuralNetwork::typeConversionToFloat(CellContent::eCellContentType type){
	switch(type){
	case CellContent::EMPTY:
		return 0;
	case CellContent::SNAKEBODY:
		return 0.2f;
	case CellContent::SNAKEHEAD:
		return 0.4f;
	case CellContent::WALL:
		return 0.6f;
	case CellContent::FOOD:
		return 0.8f;
	default:
		return 0;
	}
}
