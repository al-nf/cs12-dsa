/*
 * File: count.c
 *
 * Copyright: 2024, Alan Fung
 *
 * Description: Reads words from text file, location given as 
 * first line of cmdline argument
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 30 // arbitrary

int main(int argc, char** argv)
{
	FILE* fp;
	int wordcount;
	char word[MAX_WORD_LENGTH];

	// checks if there are two arguments
	if (argc != 2)
	{
		fprintf(stderr, "missing filename\n");
	}

	// file pointer setup
	fp = fopen(argv[1], "r");
	if (fp == NULL) // returns 0 if the file is not there
	{
        	printf("file does not exist");
        	return 0;
	}


	wordcount = 0;
	while (fscanf(fp, "%s", word) == 1) // every time there is a string, add 1 to wordcount
	{
		wordcount++;
	}
	fclose(fp);
    

	printf("%d total words\n", wordcount);


}
