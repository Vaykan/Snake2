#ifndef SRC_NEURALNETWORK_H_
#define SRC_NEURALNETWORK_H_

class Neuron{
public:
	void setValue(float inputValue, float weight);
	float getValue();
private:
	static float sigmoid(float x);
	float value;
};
class NeuralNetwork {
public:
	void randWeightStorage();
	float *weightStorage[10752];
};

#endif
