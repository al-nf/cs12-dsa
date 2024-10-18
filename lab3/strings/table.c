#include <stdio.h>
#include <string.h>
#include <bool.h>
#include "set.h"
#include <assert.h>

typedef struct set
{
	int n; // count
	int m; // max length 
	char **data;
	bool *flags; // FALSE: deleted | TRUE: filled | NULL: empty
} SET;

SET *createSet( int maxElts )
{
	SET *sp;
	sp = malloc(sizeof(SET));
	assert(sp != NULL);
	sp->n = 0;
	sp->m = maxElts;
	sp->data = malloc(sizeof(char*)*maxElts);
	sp->flags = malloc(sizeof(bool*)*maxElts);
	assert(sp->data != NULL);
	assert(sp->flags != NULL);

	return sp;	
}

void destroySet ( SET *sp )
{
	assert(sp != NULL);
	for (int i = 0; i < sp->n; i++) // frees data
	{
		free(sp->data[i]);
	}
	free(sp->data);

	for (int i = 0; i < sp->n; i++) // frees flags
	{
		free(sp->flags[i]);
	}
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
	assert(sp != NULL && elt != NULL && ((sp->n) < (sp->m)));
	int hidx = (strhash(elt))%(sp->m); // home index
	for (int i = hidx; i < ((sp->m)+hidx); i++)
	{
		if ((flags[i%(sp->m)] == FALSE) || (flags[i%(sp->m)] == NULL))
		{
			data[i%(sp->m)] = strdup(elt);
			*flags[i%(sp->m)] = TRUE;
			break;
		}
	}

	
}

void removeElement ( SET *sp, char *elt )
{
	assert(sp != NULL && elt != NULL && ((sp->n) > 0));
	int hidx = (strhash(elt))%(sp->m); // home index
	for (int i = hidx; i < ((sp->m)+hidx); i++)
	{
		if ((flags[i%(sp->m)] == TRUE && (strcmp(elt, data[i%sp->m] == 0))))
		{
			data[i%(sp->m)] = NULL;
			*flags[i%(sp->m)] = FALSE;
			break;
		}
	}
}

char *findElement ( SET *sp, char *elt )
{
	assert(sp != NULL && elt != NULL && ((sp->n) > 0) && ((sp->n) < (sp->m)));
	int hidx = (strhash(elt))%(sp->m); // home index
	for (int i = hidx; i < ((sp->m)+hidx); i++)
	{
		if (strcmp(data[i%(sp->m)], elt) == 0)
		{
			return elt;
		}
		if ((flags[i%(sp->m)] == NULL))
		{
			return NULL; // element not in SET
		}
	}
}

char **getElements ( SET *sp )
{
	// writ ehtis later
}

unsigned strhash ( char *s )
{
	unsigned hash = 0;
	while (*s != '\0')
		hash = ++((31 * hash) + *s);
	return hash;
}


