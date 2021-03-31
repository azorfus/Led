/*
 *	Writer: Azorfus
 *	Redistributable Code
 *	Under Development!
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "String_Lib.h"

#define MAX_BUFFER 1260

FILE* GivenFile;
int LineNumber = 1;
bool Editing = true;
char UserInput[128];
char* Tok;
int Lines[100][2];
String FileBuffer;

// size of user input string
size_t ENT = 0;

void OpenFile(char* filename)
{
	GivenFile = fopen(filename , "w+");
	if (GivenFile == NULL)
	{
		GivenFile = fopen("untitled", "w+");
	}
}

int main(int argc, char** argv)
{
	String_init(&FileBuffer);
	char* FileARG = argv[1];
	OpenFile(FileARG);
	String_fread(&FileBuffer, GivenFile);
	String_fwrite_stdout(&FileBuffer);
	return 0;
}
