#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "String_Lib.h"

void String_init(String* str)
{
	str->Data = NULL;
	str->Len = 0;
}

void String_charp(String* dest, const char* Source)
{
	dest->Len = strlen(Source);
	dest->Data = malloc(dest->Len + 1);
	strcpy(dest->Data, Source);
}

void String_alloc_size(String* str, size_t size)
{
	str->Data = malloc(size);
	str->Len = size-1;
}

void String_realloc(String* str, size_t size)
{
	str->Data = realloc(str->Data, str->Len + size);
}

void String_fread(String* str, FILE* source)
{
	fseek(source, 0, SEEK_END);
	size_t fileSize = ftell(source);
	str->Data = malloc(fileSize + 1);
	str->Len = fileSize + 1;
	rewind(source);
	fread(str->Data, 1, fileSize, source);
//	str->Data[str->Len] = '\0';
}

void String_fwrite_stdout(String* str)
{
	fwrite(str->Data, sizeof(char), str->Len, stdout);
}

void String_fwrite(String* str, FILE* dest)
{
	fwrite(str->Data, sizeof(char), str->Len, dest);	
}

void String_append(String* str, const char* source)
{
	size_t source_len = strlen(source);
	str->Data = realloc(str->Data, str->Len + source_len + 1);
	char* end_of_dst = str->Data  + str->Len;
	str->Len += source_len;
	strcpy(end_of_dst, source);	
}

void String_append_string(String* str, String* source)
{
	str->Data = realloc(str->Data, str->Len + source->Len + 1);
	char* end_of_dst = str->Data  + str->Len;
	str->Len += source->Len;
	strcpy(end_of_dst, source->Data);	
}

void String_resize(String* str, size_t resize, char fill_char)
{
	str->Data = realloc(str->Data, str->Len + resize + 1);
	//str->Data =  
}

void String_destroy(String* str)
{
	free(str->Data);
	str->Data = NULL;
	str->Len = 0;
}

void trynow(String* str)
{
	printf("%s, %li", str->Data, str->Len);
}
