#include "Field.h"
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

int main() {
	Field fill;
	while(fill.gameIsPlaying()){
		this_thread::sleep_for(chrono::milliseconds(400));
		fill.step();
		fill.UIDraw();
	}
	cout << " Game Over" << endl;
	system("pause");
	return 0;
}
cout << "f";
