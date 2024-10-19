#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "set.h"
#include <assert.h>

typedef struct set
{
	int n; // count
	int m; // max length 
	char **data;
	char *flags;
} SET;

SET *createSet( int maxElts )
{
	SET *sp;
	sp = malloc(sizeof(SET));
	assert(sp != NULL);
	sp->n = 0;
	sp->m = maxElts;
	sp->data = malloc(sizeof(char*)*maxElts);
	sp->flags = malloc(sizeof(char)*maxElts);
	for (int i = 0; i < maxElts; i++)
	{
		sp->flags[i] = 'E';
	}
	assert(sp->data != NULL);
	assert(sp->flags != NULL);

	return sp;	
}
static unsigned strhash ( char *s )
{
	unsigned hash = 0;
	while (*s != '\0')
	{
		hash = 31 * hash + *s ++;
	}
	return hash;
}



static int search ( SET *sp, char *elt, bool *found )
{
	assert(sp != NULL);

	*found = false;
	int idx = (strhash(elt)%(sp->m));
	int home = idx; // home location
	int firstdel = -1;

	while (! *found)
	{
		if (sp->flags[idx%(sp->m)] == 'F') // if flag filled
		{
			if ((strcmp(sp->data[idx%(sp->m)], elt))== 0) // if element is the same
			{
				*found = true;
				return (idx%(sp->m));
			}
		}
		if ((sp->flags[idx%(sp->m)]) == 'E') // if flag empty
		{
			return (idx%(sp->m));
		}
		if ((sp->flags[idx%(sp->m)]) == 'D') // if flag delete
		{
			firstdel = (idx%(sp->m));
		}
		if ((idx - home) >= (sp->m))
		{
			break;
		}
		++idx;
	}
	return firstdel;
}

void destroySet ( SET *sp ) 
{
	assert(sp != NULL);
	for (int i = 0; i < (sp->m); i++) // frees data
	{
		if (sp->flags[i] != 'D')
		{
			free(sp->data[i]);
		}
	}
	free(sp->data);
	free(sp->flags);

	free(sp); // frees set
}

int numElements ( SET *sp )
{
	assert(sp != NULL);
	return (sp->n);
}

void addElement ( SET *sp, char *elt )
{
	assert(sp != NULL);
	bool found = false;
	int idx = search(sp, elt, &found);
	if (!found && idx != -1)
	{
		sp->data[idx] = strdup(elt);
		sp->flags[idx] = 'F';
		++(sp->n);

	}
}

void removeElement ( SET *sp, char *elt )
{
	assert(sp != NULL);
	bool found = false;
	int idx = search(sp, elt, &found);
	if (found)
	{
		free(sp->data[idx]);
		sp->flags[idx] = 'D';
		--(sp->n);
	}
}
char *findElement ( SET *sp, char *elt )
{
	assert(sp != NULL);
	bool found = false;
	int idx = search(sp, elt, &found);
	if (found)
	{
		return sp->data[idx];
	}
	return NULL;
}

char **getElements ( SET *sp )
{
	assert(sp != NULL);
	int j = 0; // second increment variable
	char **strs = malloc(sizeof(char*)*(sp->n));
	for (int i = 0; i < (sp->m); i++)
	{
		
		if (sp->flags[i] == 'F')
		{
			strs[j] = sp->data[i];
			++j;
		}
	}
	return strs;
}


