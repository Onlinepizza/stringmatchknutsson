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

#define INITIAL_SIZE 500000

void searchMenu(char * textbuffer);
string readFile(string filename);
void expandArr(char * text, int * max);


main(){
	int choice;
	choice = 0;
	string textbuffer = readFile("string.txt");
	printf("press 1 for search, press 2 for test\n");
	choice = GetInteger();
	switch (choice)
	{
	case 1:
		searchMenu(textbuffer);
		break;
	case 2:
		testStringMatch(textbuffer);
		break;
	case 3:
		ordOfGrowth(textbuffer);
	default:
		exit(0);
	}
	
	getchar();
}

void searchMenu(char * textbuffer){
	string pattern;
	printf("Enter pattern\n");
	pattern = GetLine();
	
	bruteForceSearch(textbuffer, pattern);
	horSpoolSearch(textbuffer, pattern);

}




string readFile(string filename){
	char * text;
	FILE *textfile;
	char element;
	int sentinel, i, currentmax;
	text = NewArray(INITIAL_SIZE, char);
	currentmax = INITIAL_SIZE;
	i = -1;
	sentinel = 0;
	textfile = fopen(filename, "r");
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
	return text;
}

void expandArr(char * text, int * max){
	int i, currentmax;
	char * temp;
	currentmax = 0;
	currentmax = *max;
	currentmax = currentmax * 2;
	temp = NewArray(currentmax, char);
	for (i = 0; i < currentmax; i++){
		temp[i] = text[i];
	}
	FreeBlock(text);
	text = NewArray(currentmax, char);
	for (i = 0; i < currentmax; i++){
		text[i] = temp[i];
	}
	FreeBlock(temp);
	*max = currentmax;
}