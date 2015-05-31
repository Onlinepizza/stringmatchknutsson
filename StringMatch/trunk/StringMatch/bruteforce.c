#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "simpio.h"
#include "strlib.h"
#include "genlib.h"

bool searchString(string text, string pattern, int * nComparisons);

int bruteForce(char * text, string pattern){
	bool match;
	int nComparisons;
	nComparisons = 0;
	match = searchString(text, pattern, &nComparisons);
	if (match == TRUE){
		//printf("***********************BRUTEFORCE****************************\n");
		//printf("The pattern was found in the text\n Number of comparisons: %d", nComparisons);
		return nComparisons;
	}
	else{
		//printf("***********************BRUTEFORCE****************************\n");
		//printf("The pattern was NOT found in the text\n Number of comparisons: %d", nComparisons);
		return nComparisons;
	}

	getchar();
}

void bruteForceSearch(char * text, string pattern){
	bool match;
	int nComparisons;
	nComparisons = 0;
	match = searchString(text, pattern, &nComparisons);
	if (match == TRUE){
		printf("***********************BRUTEFORCE****************************\n");
		printf("MATCH! Number of comparisons: %d", nComparisons);
	}
	else{
		printf("***********************BRUTEFORCE****************************\n");
		printf("FAIL! Number of comparisons: %d", nComparisons);
	}

	getchar();
}

bool searchString(string text, string pattern, int * nComparisons){
	int i, j, textlen, patlen, comparisons;
	textlen = StringLength(text);
	patlen = StringLength(pattern);
	comparisons = 0;
	for (i = 0; i <= (textlen - patlen); i++){
		for (j = 0; j < patlen; j++){
			if(pattern[j] != text[i + j]){
				comparisons++;
				break;
			} 
			else{
				comparisons++;
				if (j == patlen - 1){
					*nComparisons = comparisons;
					return TRUE;
				}
			}
		}
	}
	*nComparisons = comparisons;
	return FALSE;

}