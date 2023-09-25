#include "Util.h"
#include <random>
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
	const float min_value = -0.015f;
	const float max_value = 0.015f;
	uniform_real_distribution<float> distribution(min_value, max_value);
	return distribution(mersenne);
}
