#include <iostream>
#include <cmath>
#include "Util.h"

#include "NeuralNetwork.h"

void Neuron::setValue(float inputValue, float weight){
	inputValue *= weight;
	value = sigmoid(inputValue);
}
float Neuron::getValue(){
	return value;
}

float Neuron::sigmoid(float x){
	return 1.0 / (1.0 + std::exp(-x));
}

void NeuralNetwork::randWeightStorage(){
	for(int x = 0; x < 10752; x++){
		*weightStorage[x] += getRandNumFloatSmall();
		if(*weightStorage[x] < 0)
			weightStorage[x] = 0;
	}
}
