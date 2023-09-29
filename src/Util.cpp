#include <random>

#include "Util.h"

using namespace std;

int getRandNumInt(){
	static random_device rd;
	static mt19937 mersenne(rd());
	uniform_int_distribution<int> distribution(0, 9);
	return distribution(mersenne);
}

float getRandNumFloatSmall(){
	static random_device rd;
	static mt19937 mersenne(rd());
	uniform_real_distribution<float> distribution(-0.015f, 0.015f);
	return distribution(mersenne);
}

float getRandNumFloatFrom0to1(){
	static random_device rd;
	static mt19937 mersenne(rd());
	uniform_real_distribution<float> distribution(0, 1);
	return distribution(mersenne);
}
