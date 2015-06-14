#ifndef _test_h
#define _test_h

#include <stdio.h>
#include "genlib.h"
#include "horspool.h"

#define INITIAL_SIZE 5000

typedef struct{
	int fivepat[50];
	int tenpat[50];
	int twentypat[50];
	int lowfivepat[50];
	int lowtenpat[50];
	int lowtwentypat[50];
} *resultT;

typedef struct{
	int * nComps;
} *growthT;

typedef struct{
	string algorithm;
	growthT five;
	growthT ten;
	growthT twenty;
	growthT lowfive;
	growthT lowten;
	growthT lowtwenty;
	int arrSize;
	int * textLen;
} *ordGrowthT;

string randomPattern(string pattern);
string generatePattern(int patternLenght, char * text);
string generateLowPattern(int patternLenght, char * text);
int maxArr(int * frequenciesTemp, int size);
int minArr(int * frequenciesTemp, int size);
shiftTableT Frequencies(char * text);
int sumArr(int * arr, int size);
string readFileTest(string filename, int inputSize);
void ordOfGrowth(string text, ordGrowthT horspool, ordGrowthT bruteforce);
void testStringMatch(char * textbuffer, char * newtext, ordGrowthT horspool, ordGrowthT bruteforce, int index);
ordGrowthT initOrdGrowth(string algorithm, int size);
growthT initGrowth(int size);
void createGrowthFile(ordGrowthT algorithm);

#endif