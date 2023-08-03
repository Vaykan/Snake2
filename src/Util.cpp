#include "Util.h"
#include <random>
using namespace std;

int getRandNumInt(){
	static random_device rd;
	static mt19937 mersenne(rd());
	uniform_int_distribution<int> distribution(0, 9);
	return distribution(mersenne);
}
