#include "InputScanner.h"
#include "conio.h"

direction inputDir (){
	direction dir;
	while(kbhit()){
		switch(getch()){
		case 'w' : dir = UP;
		break;
		case 'd' : dir = RIGHT;
		break;
		case 's' : dir = DOWN;
		break;
		case 'a' : dir = LEFT;
		}
	}
	return dir;
}

