#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "simpio.h"
#include "strlib.h"
#include "horspool.h"
#include "genlib.h"
#include "bruteforce.h"
#include "random.h"
#include <string.h>
#include "test.h"

string randomPattern(string pattern){
	int i, size;
	char *randPat;
	size = 0;
	size = StringLength(pattern)+1;
	randPat = NewArray(size, char);
	for(i=0; i<size; i++){
		randPat[i] = pattern[RandomInteger(0,size - 2)];
	}
	randPat[i] = '\0';
	return randPat;
}

string generatePattern(int patternLenght, char * text){
	shiftTableT frequencies;
	char * pattern;
	int i;
	int * frequenciesTemp;
	frequencies = Frequencies(text);
	pattern = NewArray(patternLenght + 1, char);
	frequenciesTemp = NewArray(StringLength(frequencies->alphabet), int);
	for (i = 0; i < StringLength(frequencies->alphabet); i++){
		frequenciesTemp[i] = frequencies->shift[i];
	}
	for (i = 0; i < patternLenght; i++){
		pattern[i] = frequencies->alphabet[maxArr(frequenciesTemp, StringLength(frequencies->alphabet))];
	}
	pattern[i] = '\0';

	return pattern;
}

string generateLowPattern(int patternLenght, char * text){
	shiftTableT frequencies;
	char * pattern;
	int i;
	int * frequenciesTemp;
	frequencies = Frequencies(text);
	pattern = NewArray(patternLenght + 1, char);
	frequenciesTemp = NewArray(StringLength(frequencies->alphabet), int);
	for (i = 0; i < StringLength(frequencies->alphabet); i++){
		frequenciesTemp[i] = frequencies->shift[i];
	}
	for (i = 0; i < patternLenght; i++){
		pattern[i] = frequencies->alphabet[minArr(frequenciesTemp, StringLength(frequencies->alphabet))];
	}
	pattern[i] = '\0';

	return pattern;
}

int maxArr(int * frequenciesTemp, int size ){
	int i, max;
	max = -1;
	for (i = 0; i<size; i++){
		if (frequenciesTemp[i]>=max){
			max = i;
		}	
	}
	frequenciesTemp[max] = 0;
	return(max);
}

int minArr(int * frequenciesTemp, int size ){
	int i, min;
	min = 10000000000000;
	for (i = 0; i<size; i++){
		if (frequenciesTemp[i]<=min && frequenciesTemp[i] > 0){
			min = i;
		}	
	}
	frequenciesTemp[min] = 0;
	return(min);
}

shiftTableT Frequencies(char * text){
	int i,j;
	shiftTableT freq;
	freq = initializeShiftTable("");
	for (i = 0; i < StringLength(text); i++){
		for (j = 0; j < StringLength(freq->alphabet); j++){
			if (text[i] == freq->alphabet[j])
				freq->shift[j]++;
		}
	}
	return freq;
}

int sumArr(int * arr, int size){
	int i, sum;
	sum = 0;
	for (i=0;i<size;i++){
		sum += arr[i];
	}
	return sum;
}

string readFileTest(string filename, int inputSize){
	char * text;
	FILE *textfile;
	char element;
	int i;
	text = NewArray(INITIAL_SIZE, char);
	i = 0;
	textfile = fopen(filename, "r");
	while (i < inputSize){
		element = getc(textfile);
		text[i] = element;
	}
	text[i] = '\0';
	fclose(textfile);
	return text;
}

void ordOfGrowth(string text){
	int i, size, newSize;
	double div;
	i = 0;
	size = 0;
	newSize = 0;
	div = 1;
	string pattern;
	growthT growth;
	growth = (growthT)GetBlock(sizeof * growth);
	growth->type = "horspool";
	growth->textLen = NewArray(100, int);
	growth->nComps = NewArray(100, int);
	Randomize();
	pattern = generatePattern(10, text);
	size = StringLength(text);
	newSize = size;
	free(text);
	while (i < 100){
		//anrop till readFileTest
		//s�tt in text i horspool/bruteforce
		growth->textLen[i] = newSize;
		growth->nComps[i] = horSpool(readFileTest("string.txt", newSize), pattern);
		div -= 0,01;
		newSize *= div;
		i++;
	}

}



void testStringMatch(char * textbuffer){
	int i;
	string pattern;
	resultT result;
	result = (resultT)GetBlock(sizeof * result);

	/****EXPERIMENT************/
	/**********HIGH************/

	Randomize();
	printf("**********************************************************\n");
	printf("HORSPOOL\n\n");
	printf("Patterns consisting of the 5, 10 and 20 most common letters\nin the text will be generated\neach will be shuffled and retried 50 times.\n");
	getchar();

	pattern = generatePattern(5, textbuffer);
	for (i = 0; i < 50; i++){
		result->fivepat[i] = horSpool(textbuffer, randomPattern(pattern));
	}

	pattern = generatePattern(10, textbuffer);
	for (i = 0; i < 50; i++){
		result->tenpat[i] = horSpool(textbuffer, randomPattern(pattern));
	}

	pattern = generatePattern(20, textbuffer);
	for (i = 0; i < 50; i++){
		result->twentypat[i] = horSpool(textbuffer, randomPattern(pattern));
	}

	/********LOW*********/

	printf("Patterns consisting of the 5, 10 and 20 LEAST common letters\nin the text will be generated\neach will be shuffled and retried 50 times.\n");
	getchar();

	pattern = generateLowPattern(5, textbuffer);
	for (i = 0; i < 50; i++){
		result->lowfivepat[i] = horSpool(textbuffer, randomPattern(pattern));
	}

	pattern = generateLowPattern(10, textbuffer);
	for (i = 0; i < 50; i++){
		result->lowtenpat[i] = horSpool(textbuffer, randomPattern(pattern));
	}

	pattern = generateLowPattern(20, textbuffer);
	for (i = 0; i < 50; i++){
		result->lowtwentypat[i] = horSpool(textbuffer, randomPattern(pattern));
	}

	printf("MOST COMMON LETTERS\n");
	printf("5 letters: %d\n", (sumArr(result->fivepat, 50) / 50));
	printf("10 letters: %d\n", (sumArr(result->tenpat, 50) / 50));
	printf("20 letters: %d\n", (sumArr(result->twentypat, 50) / 50));

	printf("LEAST COMMON LETTERS\n");
	printf("5 letters: %d\n", (sumArr(result->lowfivepat, 50) / 50));
	printf("10 letters: %d\n", (sumArr(result->lowtenpat, 50) / 50));
	printf("20 letters: %d\n", (sumArr(result->lowtwentypat, 50) / 50));
	printf("**********************************************************\n\n");
	getchar();


	/****EXPERIMENT************/
	/**********HIGH************/

	printf("**********************************************************\n");
	printf("BRUTEFORCE\n");
	printf("Patterns consisting of the 5, 10 and 20 most common letters\nin the text will be generated\neach will be shuffled and retried 50 times.\n");
	getchar();

	pattern = generatePattern(5, textbuffer);
	for (i = 0; i < 50; i++){
		result->fivepat[i] = bruteForce(textbuffer, randomPattern(pattern));
	}

	pattern = generatePattern(10, textbuffer);
	for (i = 0; i < 50; i++){
		result->tenpat[i] = bruteForce(textbuffer, randomPattern(pattern));
	}

	pattern = generatePattern(20, textbuffer);
	for (i = 0; i < 50; i++){
		result->twentypat[i] = bruteForce(textbuffer, randomPattern(pattern));
	}

	/********LOW*********/

	printf("Patterns consisting of the 5, 10 and 20 LEAST common letters\nin the text will be generated\neach will be shuffled and retried 50 times.\n");
	getchar();

	pattern = generateLowPattern(5, textbuffer);
	for (i = 0; i < 50; i++){
		result->lowfivepat[i] = bruteForce(textbuffer, randomPattern(pattern));
	}

	pattern = generateLowPattern(10, textbuffer);
	for (i = 0; i < 50; i++){
		result->lowtenpat[i] = bruteForce(textbuffer, randomPattern(pattern));
	}

	pattern = generateLowPattern(20, textbuffer);
	for (i = 0; i < 50; i++){
		result->lowtwentypat[i] = bruteForce(textbuffer, randomPattern(pattern));
	}

	printf("MOST COMMON LETTERS\n");
	printf("5 letters: %d\n", (sumArr(result->fivepat, 50) / 50));
	printf("10 letters: %d\n", (sumArr(result->tenpat, 50) / 50));
	printf("20 letters: %d\n", (sumArr(result->twentypat, 50) / 50));

	printf("LEAST COMMON LETTERS\n");
	printf("5 letters: %d\n", (sumArr(result->lowfivepat, 50) / 50));
	printf("10 letters: %d\n", (sumArr(result->lowtenpat, 50) / 50));
	printf("20 letters: %d\n", (sumArr(result->lowtwentypat, 50) / 50));
	printf("**********************************************************\n");

	//printf("%s", textbuffer);
	getchar();
}