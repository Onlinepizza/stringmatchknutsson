#ifndef _test_h
#define _test_h

#include <stdio.h>
#include "genlib.h"
#include "horspool.h"

#define INITIAL_SIZE 500000

typedef struct{
	int fivepat[50];
	int tenpat[50];
	int twentypat[50];
	int lowfivepat[50];
	int lowtenpat[50];
	int lowtwentypat[50];
} *resultT;

typedef struct{
	string type;
	int * textLen;
	int * nComps;
	int arrSize;
} *growthT;

string randomPattern(string pattern);
string generatePattern(int patternLenght, char * text);
string generateLowPattern(int patternLenght, char * text);
int maxArr(int * frequenciesTemp, int size);
int minArr(int * frequenciesTemp, int size);
shiftTableT Frequencies(char * text);
int sumArr(int * arr, int size);
string readFileTest(string filename, int inputSize);
void ordOfGrowth(string text, growthT horspool, growthT bruteforce);
void testStringMatch(char * textbuffer);
growthT initGrowth(string algorithm, int size);
void createGrowthFile(growthT horspool, growthT bruteforce);

#endif