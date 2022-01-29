#ifndef SEM_H
#define SEM_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "data.h"
#include "utils.h"



void sem();

//Semantic Rule 1 : table names must be unique
void checkTableNamesDeclarations();

//Semantic Rule 2 : column names in a table must be unique
void checkColumnNamesDeclarations();

//Semantic Rule 3 : table directive must not be used more than one time in a table
void checkTableDirectives();

//Semantic Rule 4 : column directive must not be used more than one time in a column
void checkColumnDirectives();

//Semantic Rule 5 : table,column and view name lengths must not exceed 128 characters
void checkNameLength(char* name);

//Semantic Rule 6 : tables referenced in views must be declared in the same file
void checkViewsTables();


#endif