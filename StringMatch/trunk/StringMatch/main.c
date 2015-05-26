#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "simpio.h"
#include "strlib.h"
#include "horspool.h"
#include "genlib.h"
#include "brutefroce.h"
#include "random.h"
#include <string.h>

#define INITIAL_SIZE 500000

string generatePattern(int patternLenght, char * text);
int maxArr(int * frequenciesTemp, int size);
shiftTableT Frequencies(char * text);
void readFile(char * text);
void expandArr(char * text, int * max);

main(){
	//string pattern;
	char * textbuffer;
	string pattern;
	//bool match, match2;
	textbuffer = NewArray(INITIAL_SIZE, char);
	readFile(textbuffer);
	/*printf("enter the pattern you want to search for\n");
	pattern = GetLine();
	match = horSpool(textbuffer, pattern);
	match2 = bruteForce(textbuffer, pattern);
	*/
	pattern = generatePattern(5, textbuffer);
	printf("%s", pattern);


	getchar();
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

int maxArr(int * frequenciesTemp, int size ){
	int i, max;
	max = -1;
	for (i = 0; i<size; i++){
		if (frequenciesTemp[i]>max){
			max = i;
		}	
	}
	frequenciesTemp[max] = 0;
	return(max);
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

void readFile(char * text){
	FILE *textfile;
	char element;
	int sentinel, i, currentmax;
	currentmax = INITIAL_SIZE;
	i = -1;
	sentinel = 0;
	textfile = fopen("string.txt", "r");
	while (sentinel == 0){
		if (i >= currentmax - 1){
			expandArr(text, &currentmax);
		}
		i++;
		element = getc(textfile);
		if (element == EOF){
			text[i] = '\0';
			sentinel = 1;
			break;
		}
		else{
			text[i] = element;
		}
	}
	fclose(textfile);
}

void expandArr(char * text, int * max){
	char * temp;
	int i, currentmax;
	currentmax = max;
	temp = NewArray(currentmax * 2, char);
	for (i = 0; i < currentmax; i++){
		temp[i] = text[i];
	}
	free(text);
	text = NewArray(currentmax * 2, char);
	for (i = 0; i < currentmax * 2; i++){
		text[i] = temp[i];
	}
	free(temp);
	max = currentmax * 2;
}
