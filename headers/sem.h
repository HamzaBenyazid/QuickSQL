#ifndef SEM_H
#define SEM_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "data.h"



void sem();
int countNumberOfTables();
int countNumberOfViews();
int countNumberOfColumns(Table table);
int countNumberOfTableDirectives(Table table);
void checkTableNamesDeclarations();
void checkColumnNamesDeclarations();
void checkTableDirectives();
void checkColumnDirectives();

#endif