#include <iostream>
#include <chrono>
#include <thread>

#include "Field.h"
#include "NeuralNetwork.h"

using namespace std;

int main() {
	NeuralNetwork *n;
	n = new NeuralNetwork;
	Field fill(n);
	while(fill.gameIsPlaying()){
		this_thread::sleep_for(chrono::milliseconds(400));
		fill.step();
		fill.UIDraw();
	}
	cout << " Game Over" << endl;
	system("pause");
	return 0;
}

