#ifndef STRING_LIB_H
#define STRING_LIB_H

#include <stdio.h>
#include <string.h>

typedef struct String
{
	char* Data;
	size_t Len;
} String;

void String_init(String* str);
void String_charp(String* dest, const char* Source);
void String_alloc_size(String* str, size_t size);
void String_realloc(String* str, size_t size);
void String_fread(String* str, FILE* source);
void String_fwrite_stdout(String* str);
void String_fwrite(String* str, FILE* dest);
void String_append(String* str, const char* source);
void String_append_string(String* str, String* source);
void String_remsubstr(String *str, const char *toRemove);
void String_resize(String* str, size_t newsize, char fill_char);
void String_destroy(String* str);
void trynow(String* str);

#endif // !STRING_LIB
