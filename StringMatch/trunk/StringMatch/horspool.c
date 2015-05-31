#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "simpio.h"
#include "strlib.h"
#include "horspool.h"

static bool searchString(shiftTableT shifttable, string text);
static void createAlphabet(shiftTableT shifttable);
static void createShift(shiftTableT shifttable);

int horSpool(char * text, string pattern){
	shiftTableT shifttable;
	bool match;
	shifttable = initializeShiftTable(pattern);
	match = searchString(shifttable, text);

	if (match == TRUE){
		//printf("*************HORSPOOL**************\n");
		//printf("MATCH! Number of comparisons %d\n", shifttable->nComps);
		return shifttable->nComps;
	}
	else{
		//printf("*************HORSPOOL**************\n");
		//printf("FAIL! Number of comparisons: %d\n", shifttable->nComps);
		return shifttable->nComps;
	}
}

void horSpoolSearch(char * text, string pattern){
	shiftTableT shifttable;
	bool match;
	shifttable = initializeShiftTable(pattern);
	match = searchString(shifttable, text);

	if (match == TRUE){
		printf("*************HORSPOOL**************\n");
		printf("MATCH! Number of comparisons %d\n", shifttable->nComps);
	}
	else{
		printf("*************HORSPOOL**************\n");
		printf("FAIL! Number of comparisons: %d\n", shifttable->nComps);
		return shifttable->nComps;
	}
}

static bool searchString(shiftTableT shifttable, string text){
	int i, j, searchpattern, nshifts, stopvalue;
	searchpattern = StringLength(shifttable->pattern);
	i = 0;
	nshifts = 0;
	stopvalue = StringLength(text) - searchpattern;
	while (i <= stopvalue){
		for (j = searchpattern-1; j > -1; j--){
			if (shifttable->pattern[j] != text[i + j]){
				shifttable->nComps++;
				nshifts = FindChar(text[i+(searchpattern-1)], shifttable->alphabet, 0);
				i += shifttable->shift[nshifts];
				break;
			}
			else{
				shifttable->nComps++;
				if (j == 0){
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

shiftTableT initializeShiftTable(string ipattern){
	shiftTableT shifttable;
	shifttable = (shiftTableT)GetBlock(sizeof * shifttable);
	shifttable->pattern = ipattern;
	createAlphabet(shifttable);
	shifttable->shift = NewArray(StringLength(shifttable->alphabet), int);
	createShift(shifttable);
	shifttable->nComps = 0;
	return shifttable;
}

static void createAlphabet(shiftTableT shifttable){
	int i;
	char letter;
	shifttable->alphabet = NewArray(260,char);
	for (i = 1; i < 256; i++){
		letter = i;
		shifttable->alphabet[i-1] = letter;
	}
	shifttable->alphabet[i] = '\0';
}

static void createShift(shiftTableT shifttable){
	int i,j,maxshift;
	maxshift = StringLength(shifttable->pattern);
	for (i = 0; i < StringLength(shifttable->alphabet); i++){
		shifttable->shift[i] = maxshift;
	}
	for (j = 0; j < maxshift-1; j++){
		for (i = 0; i < StringLength(shifttable->alphabet); i++){
			if (shifttable->pattern[j] == shifttable->alphabet[i]){
				shifttable->shift[i] = maxshift - (j+1);
				break;
			}
		}
	}
}