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
	min = 1000000;
	for (i = 0; i<size; i++){
		if (frequenciesTemp[i] < min && frequenciesTemp[i] > 0){
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
		i++;
	}
	text[i] = '\0';
	fclose(textfile);
	return text;
}

ordGrowthT initOrdGrowth(string algorithm, int size){
	ordGrowthT Ogrowth;
	int arr;
	arr = size / 50;
	Ogrowth = (ordGrowthT)GetBlock(sizeof * Ogrowth);
	Ogrowth->algorithm = algorithm;
	Ogrowth->five = initGrowth(arr);
	Ogrowth->ten = initGrowth(arr);
	Ogrowth->twenty = initGrowth(arr);
	Ogrowth->lowfive = initGrowth(arr);
	Ogrowth->lowten = initGrowth(arr);
	Ogrowth->lowtwenty = initGrowth(arr);
	Ogrowth->arrSize = size;
	Ogrowth->textLen = NewArray(size, int);

	return Ogrowth;
}

growthT initGrowth(int size){
	growthT growth;
	growth = (growthT)GetBlock(sizeof * growth);
	growth->nComps = NewArray(size, int);
	return growth;
}

void createGrowthFile(ordGrowthT algorithm){
	int i, stop;
	stop = (algorithm->arrSize/50);
	FILE *outfile;
	string file;
	file = Concat(algorithm->algorithm, ".txt");
	outfile = fopen(file, "w");
	fprintf(outfile, "%s\n", algorithm->algorithm);
	//spara de vanliga mönstren
	//5
	fprintf(outfile, "\ncommon 5pattern textlen\n");
	for (i = 0; i < stop; i++){
		fprintf(outfile, "%s	", IntegerToString(algorithm->textLen[i]));
	}
	fprintf(outfile,"\ncommon 5pattern ncomps\n");
	for (i = 0; i < stop; i++){
		fprintf(outfile, "%s	", IntegerToString(algorithm->five->nComps[i]));
	}

	fprintf(outfile, "\ncommon 10pattern ncomps\n");
	for (i = 0; i < stop; i++){
		fprintf(outfile, "%s	", IntegerToString(algorithm->ten->nComps[i]));
	}
	
	fprintf(outfile, "\ncommon 20pattern ncomps\n");
	for (i = 0; i < stop; i++){
		fprintf(outfile, "%s	", IntegerToString(algorithm->twenty->nComps[i]));
	}

	//spara de ovanliga mönstren

	//5
	
	fprintf(outfile, "\nUNncommon 5pattern ncomps\n");
	for (i = 0; i < stop; i++){
		fprintf(outfile, "%s	", IntegerToString(algorithm->lowfive->nComps[i]));
	}
	//10

	fprintf(outfile, "\nUNcommon 10pattern ncomps\n");
	for (i = 0; i < stop; i++){
		fprintf(outfile, "%s	", IntegerToString(algorithm->lowten->nComps[i]));
	}
	//20
	
	fprintf(outfile, "\nUNcommon 20pattern ncomps\n");
	for (i = 0; i < stop; i++){
		fprintf(outfile, "%s	", IntegerToString(algorithm->lowtwenty->nComps[i]));
	}

	fclose(outfile);
	printf("File created");
}


void ordOfGrowth(string text, ordGrowthT horspool, ordGrowthT bruteforce){
	int i, j, size, newSize, stop, pat;
	double div;
	string newtext;
	pat = 20;
	i = pat;
	j = 0;
	size = 0;
	newSize = 0;
	div = 1;
	stop = (horspool->arrSize + pat);

	Randomize();
	size = StringLength(text);
	newSize = size;
	while (i < stop){
		printf("%d\n", i);
		newtext = readFileTest("string.txt", i);
		//markera längd på text
		
		horspool->textLen[j] = i;
		

		//markera längd på text
		bruteforce->textLen[j] = i;
		

		//räkna ut antal jämförelser
		testStringMatch(text, newtext, horspool, bruteforce, j);
		FreeBlock(newtext);
		j++;
		i = (i + 50);
	}
	createGrowthFile(horspool);
	createGrowthFile(bruteforce);
}




void testStringMatch(char * textbuffer, char * newtext, ordGrowthT horspool, ordGrowthT bruteforce, int index){
	int i, hFive, hTen, hTwenty, lFive, lTen, lTwenty;
	string pattern;
	resultT result;
	result = (resultT)GetBlock(sizeof * result);

	/****EXPERIMENT************/
	/**********HIGH************/
	/*
	printf("**********************************************************\n");
	printf("HORSPOOL\n\n");
	printf("Patterns consisting of the 5, 10 and 20 most common letters\nin the text will be generated\neach will be shuffled and retried 50 times.\n");
	*/
	pattern = generatePattern(5, textbuffer);
	for (i = 0; i < 50; i++){
		result->fivepat[i] = horSpool(newtext, randomPattern(pattern));
	}

	pattern = generatePattern(10, textbuffer);
	for (i = 0; i < 50; i++){
		result->tenpat[i] = horSpool(newtext, randomPattern(pattern));
	}

	pattern = generatePattern(20, textbuffer);
	for (i = 0; i < 50; i++){
		result->twentypat[i] = horSpool(newtext, randomPattern(pattern));
	}

	/********LOW*********/

	//printf("Patterns consisting of the 5, 10 and 20 LEAST common letters\nin the text will be generated\neach will be shuffled and retried 50 times.\n");

	pattern = generateLowPattern(5, textbuffer);
	for (i = 0; i < 50; i++){
		result->lowfivepat[i] = horSpool(newtext, randomPattern(pattern));
	}

	pattern = generateLowPattern(10, textbuffer);
	for (i = 0; i < 50; i++){
		result->lowtenpat[i] = horSpool(newtext, randomPattern(pattern));
	}

	pattern = generateLowPattern(20, textbuffer);
	for (i = 0; i < 50; i++){
		result->lowtwentypat[i] = horSpool(newtext, randomPattern(pattern));
	}

	//printf("MOST COMMON LETTERS\n");
	hFive = (sumArr(result->fivepat, 50) / 50);
	hTen = (sumArr(result->tenpat, 50) / 50);
	hTwenty = (sumArr(result->twentypat, 50) / 50);
	/*
	printf("5 letters: %d\n", hFive);
	printf("10 letters: %d\n", hTen);
	printf("20 letters: %d\n", hTwenty);
	*/
	horspool->five->nComps[index] = hFive;
	horspool->ten->nComps[index] = hTen;
	horspool->twenty->nComps[index] = hTwenty;

	//printf("LEAST COMMON LETTERS\n");
	lFive = (sumArr(result->lowfivepat, 50) / 50);
	lTen = (sumArr(result->lowtenpat, 50) / 50);
	lTwenty = (sumArr(result->lowtwentypat, 50) / 50);
	/*
	printf("5 letters: %d\n", lFive);
	printf("10 letters: %d\n", lTen);
	printf("20 letters: %d\n", lTwenty);
	*/
	horspool->lowfive->nComps[index] = lFive;
	horspool->lowten->nComps[index] = lTen;
	horspool->lowtwenty->nComps[index] = lTwenty;

	//printf("**********************************************************\n\n");
	


	/****EXPERIMENT************/
	/**********HIGH************/
	/*
	printf("**********************************************************\n");
	printf("BRUTEFORCE\n");
	printf("Patterns consisting of the 5, 10 and 20 most common letters\nin the text will be generated\neach will be shuffled and retried 50 times.\n");
	*/
	pattern = generatePattern(5, textbuffer);
	for (i = 0; i < 50; i++){
		result->fivepat[i] = bruteForce(newtext, randomPattern(pattern));
	}

	pattern = generatePattern(10, textbuffer);
	for (i = 0; i < 50; i++){
		result->tenpat[i] = bruteForce(newtext, randomPattern(pattern));
	}

	pattern = generatePattern(20, textbuffer);
	for (i = 0; i < 50; i++){
		result->twentypat[i] = bruteForce(newtext, randomPattern(pattern));
	}

	/********LOW*********/

	//printf("Patterns consisting of the 5, 10 and 20 LEAST common letters\nin the text will be generated\neach will be shuffled and retried 50 times.\n");

	pattern = generateLowPattern(5, textbuffer);
	for (i = 0; i < 50; i++){
		result->lowfivepat[i] = bruteForce(newtext, randomPattern(pattern));
	}

	pattern = generateLowPattern(10, textbuffer);
	for (i = 0; i < 50; i++){
		result->lowtenpat[i] = bruteForce(newtext, randomPattern(pattern));
	}

	pattern = generateLowPattern(20, textbuffer);
	for (i = 0; i < 50; i++){
		result->lowtwentypat[i] = bruteForce(newtext, randomPattern(pattern));
	}

	//printf("MOST COMMON LETTERS\n");
	hFive = (sumArr(result->fivepat, 50) / 50);
	hTen = (sumArr(result->tenpat, 50) / 50);
	hTwenty = (sumArr(result->twentypat, 50) / 50);
	/*
	printf("5 letters: %d\n", hFive);
	printf("10 letters: %d\n", hTen);
	printf("20 letters: %d\n", hTwenty);
	*/
	bruteforce->five->nComps[index] = hFive;
	bruteforce->ten->nComps[index] = hTen;
	bruteforce->twenty->nComps[index] = hTwenty;

	//printf("LEAST COMMON LETTERS\n");
	lFive = (sumArr(result->lowfivepat, 50) / 50);
	lTen = (sumArr(result->lowtenpat, 50) / 50);
	lTwenty = (sumArr(result->lowtwentypat, 50) / 50);
	/*
	printf("5 letters: %d\n", lFive);
	printf("10 letters: %d\n", lTen);
	printf("20 letters: %d\n", lTwenty);
	*/
	bruteforce->lowfive->nComps[index] = lFive;
	bruteforce->lowten->nComps[index] = lTen;
	bruteforce->lowtwenty->nComps[index] = lTwenty;

}
