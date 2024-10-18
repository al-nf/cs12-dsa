/*
 * File: unsorted.c
 *
 * Copyright: 2024, Alan Fung
 *
 * Description: Implementation of utility functions for an unsorted set
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "set.h"
#include <stdbool.h>

typedef struct set{
	int n; //number of elements
	int len; //length of data
	char **data; // array of string pointers
} SET;

/*
	Function name: createSet
	Time complexity: O(1)
	Description: returns a pointer to a new set with max capacity maxElts

*/
SET *createSet (int maxElts)
{
	SET *sp;
	sp = malloc(sizeof(SET));
	assert(sp != NULL);
	sp->n = 0;
	sp->len = maxElts;
	sp->data = malloc(sizeof(char*)*maxElts);
	assert(sp->data != NULL);
	
	return sp;
};

/*
 	Function name: search
	Time complexity: O(n)
	Description: returns index of elt in set. if elt is not in set, returns -1.
*/
static int search(SET *sp, char *elt)
{
	assert(sp != NULL);
	for (int i = 0; i < (sp->n); i++)
	{
		if (strcmp(sp->data[i], elt) == 0)
		{
			return i;
		}
	}	
	return -1;
}

/*
 	Function name: destroySet
	Time complexity: O(n)	
	Description: frees all the memory within the string pointer array within
	the set, and then frees the memory of the array itself.

*/
void destroySet(SET *sp)
{
	assert(sp != NULL);
	for (int i = 0; i < sp->n; i++)
	{
		free(sp->data[i]);
	}
	free(sp->data);
	free(sp);
};

/*
 	Function name: numElements
	Time complexity: O(1)
	Description: returns the number of elements in set sp
*/	
int numElements(SET *sp)
{
	assert(sp != NULL);
	return sp->n;
};

/*
 	Function name: addElement
	Time complexity: O(n)
	Description: checks whether elt already exists in the set, allocates memory, copies string elt, then adds it to the set
*/
void addElement(SET *sp, char *elt)
{
	assert(sp != NULL);
	if (search(sp,elt) == -1)
	{
		sp->data[sp->n] = strdup(elt);
		(sp->n)++;
	}
};	

/*
 	Function name: removeElement
	Time complexity: O(n)
	Description: checks if elt is in set, removes element elt from set, then fills the empty element with the last one
*/
void removeElement(SET *sp, char *elt)
{
	assert(sp != NULL);
	if (search(sp,elt) != -1)
	{
		int c = search(sp, elt);
		free(sp->data[c]);
		sp->data[c] = strdup(sp->data[(sp->n)-1]);
		(sp->n)--;
	}
};

/*
 	Function name: findElement
	Time Complexity: O(n)
	Description: returns the pointer to the matching element in the set
	else returns NULL
*/
char *findElement(SET *sp, char *elt)
{
	assert(sp != NULL);
	if (search(sp, elt) == -1){
		return NULL;
	}
	else {
		return sp->data[search(sp, elt)];
	}
};

/*
 	Function name: getElements
	Time complexity: O(n)
	Description: allocates then returns array of elements in set
*/
char **getElements(SET *sp)
{
	assert(sp != NULL);
	char **strs = malloc(sizeof(char*)*(sp->len));
	memcpy(strs, sp->data, sp->len);

	return strs;
}
