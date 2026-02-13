/*
* author: sagnik bhattacharjee
* date: feb 13, 2025
* assignment: 2.2
*/

#include "bulbasaur.h"

#define CARROTS 10
#define POTATOES 10
#define WATER 1.22

int main(int argc, char *argv[]) { 
	// normal writing to output stream
	bulbaWrite("hello from bulbasaur.h!");
	
	// formatted print
	bulbaPrintf("I have eaten %d carrots\n", CARROTS);
	
	bulbaPrintf("Carrots: %d, Potatoes: %d\n", CARROTS, POTATOES);
	
	bulbaPrintf("I drank %f litres of water\n", WATER);
	
	// throws error and kills the program
	bulbaScream("RANDOM ERROR");
}