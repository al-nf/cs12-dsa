/*
 * File: sorted.c
 *
 * Copyright: 2024, Alan Fung
 *
 * Description: Implementation of the utility functions of a sorted set.
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
	Description: creates and returns a pointer to a new set with max capacity maxElts
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
	Time complexity: O(log n)
	Description: returns index of elt in set. if elt is not in set, returns the index at which it should be inserted.
*/
static int search(SET *sp, char *elt, bool *found)
{
		
	assert(sp != NULL);
	
	*found = false;
	int lo, mid, hi;
	lo = 0;
	hi = (sp->n)-1;
	while (lo <= hi)
	{
		mid = (lo + hi)/2;
		if (strcmp(elt, sp->data[mid]) == 0)
		{
			*found = true;
			return mid;
		}
		if (strcmp(elt, sp->data[mid] ) < 0)
		{
			hi = mid - 1;
		}
		else
		{
			lo = mid + 1;
		}
	}
	return lo;
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
	Description: first checks if elt exists in set, if it does not, obtains index at which it should be placed, then shifts rest of array to the right, then inserts that element into that index
*/
void addElement(SET *sp, char *elt)
{
	assert(sp != NULL);
	bool found = false;
	int idx = search(sp, elt, &found);
	if (!found)
	{
		for (int i = (sp->n); i > idx; i--)
		{
			sp->data[i] = sp->data[i-1];
		}
		sp->data[idx] = strdup(elt);
		(sp->n)++;
	}
};	

/*
 	Function name: removeElement
	Time complexity: O(n)
	Description: removes element elt from set, then moves the rest of the set to fill the empty slot
*/
void removeElement(SET *sp, char *elt)
{
	assert(sp != NULL);
	bool found = false;
	int idx = search(sp, elt, &found);
	if (found)
	{
		for (int i = idx; i < (sp->n); i++)
		{
			sp->data[i] = sp->data[i+1];
		}	
		free(sp->data[(sp->n)]);
		(sp->n)--;
	}
};

/*
 	Function name: findElement
	Time complexity: O(log n)
	Description: returns the pointer to the matching element in the set
	else returns NULL
*/
char *findElement(SET *sp, char *elt)
{
	assert(sp != NULL);
	bool found = false;
	search(sp, elt, &found);
	if (!found)
	{
		return NULL;
	}
	else 
	{
		return sp->data[search(sp, elt, &found)];
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
