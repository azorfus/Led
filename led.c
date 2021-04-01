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
	GivenFile = fopen(filename , "r+");
	if (GivenFile == NULL)
	{
		GivenFile = fopen("untitled.txt", "w+");
	}
}

int main(int argc, char** argv)
{
	String_init(&FileBuffer);
	char* FileARG = argv[1];
	OpenFile(FileARG);
	String_fread(&FileBuffer, GivenFile);
	int I;

	if (FileBuffer.Data != NULL)
	{
		// storing newline character's index with the line number for later inserts
		int Count = 1;
		int prev;
		Lines[0][0] = 1;
		Lines[0][1] = 0;
		for (int i = 0; i < FileBuffer.Len; i++)
		{
			if (FileBuffer.Data[i] != '\n' && FileBuffer.Data[i] != '\0') continue; // ignore this iteration

			Lines[Count][0] = i + 1;
			Lines[Count - 1][1] = i - Lines[Count - 1][0];
			if (Lines[Count - 1][1] == -1)
			{
				Lines[Count - 1][1] = 0;
			}
			Count++;
			I = Count;
		}

		Lines[Count - 1][1] = FileBuffer.Len - 1 - Lines[Count - 1][0];

		Count = 0;
	}
	while(Editing)
	{
		fputs("*", stdout);
		fgets(UserInput, 128, stdin);
		Tok = strtok(UserInput, ";");
		if (strcmp(Tok, "l") == 0)
		{
			String_fwrite_stdout(&FileBuffer);
		}
		else if (strcmp(Tok, "q") == 0)
		{
			if (GivenFile != NULL)
			{
				fclose(GivenFile);
			}
			String_destroy(&FileBuffer);
			exit(0);
		}
		else if (strcmp(Tok, "a") == 0)
		{
			bool inputrun = true;
			char inputSec[559];
			String temp;
			String_init(&temp);
			while (inputrun)
			{
				fputs(": ", stdout);
				fgets(inputSec, 558, stdin);
				// check ret and do something if null
				//inputSec[559] = '\0'; // In case fgets reads 559 bytes without a nul
				if (strncmp(inputSec, "*w", 2) == 0)
				{
					String_append_string(&FileBuffer, &temp);
					String_destroy(&temp);				
					inputrun=false;
				}
				else if (strncmp(inputSec, "*q", 2) == 0)
				{
					String_destroy(&temp);
					inputrun = false;
				}
				else {
					String_append(&temp, inputSec);
					String_fwrite_stdout(&temp);
					// copying the user input into the FileBuffer
				}
			}
			inputrun = true;
		}
		else if (strcmp(Tok, "w") == 0)
		{
			String_fwrite(&FileBuffer, GivenFile);
			printf("[%ld] bytes written to file.\n", FileBuffer.Len);
		}
		else if (strcmp(Tok, "r") == 0)
		{
			int LINEchsn;
			fputs(": ", stdout);
			scanf("%d", &LINEchsn);


			int INDEXchsn, INDEXend;

			if (!(LINEchsn >= 1 || LINEchsn < I))
			{
				printf("Line does not exist!\n");
			}
			else
			{
				LINEchsn -= 1;
				INDEXchsn = Lines[LINEchsn][0];
				INDEXend = Lines[LINEchsn + 1][0];

				char* lineBeginning = FileBuffer.Data + INDEXchsn - 1;
				int count = 0;
				INDEXend += 1;

				for (int i = INDEXchsn; i < INDEXend; i++)
				{
					count++;
				}

				int lineLength = count;

				memmove(lineBeginning, lineBeginning + lineLength, FileBuffer.Len - lineLength);
			}
			//			FileBuffer = realloc(FileBuffer, fileSize - lineLength);

		}
		
	}

	return 0;
}
