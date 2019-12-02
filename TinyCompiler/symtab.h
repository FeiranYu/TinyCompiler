#pragma once
#ifndef _SYMTAB_H_
#define _SYMTAB_H_
#include"globals.h"
void st_insert(char* name, int lineno, int loc);

int st_lookup(char* name);

void printSymTab(FILE* listing);
#endif