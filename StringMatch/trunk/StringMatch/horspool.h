#ifndef _horspool_h
#define _horspool_h

#include <stdio.h>
#include "genlib.h"

typedef struct{
	string pattern;
	char * alphabet;
	int * shift;
	int nComps;
} *shiftTableT;

bool horSpool(char * text, string pattern);
shiftTableT initializeShiftTable(string ipattern);

#endif