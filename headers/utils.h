#ifndef UTILS_H
#define UTILS_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"data.h"
#include"lex.h"

void initTablesAndViews();

void addTableName(char tableName[5]);
void addTableDirective(CODE_LEX tableDirective);
void addTableDirectiveArgument(char* argument);
void addColumnName(char* columnName);
void addColumnType(CODE_LEX type);
void addColumnDirective(CODE_LEX columnDirective);
void addColumnDirectiveArgument(char* argument);

void freeTablesAndViews();

ColumnType mapCodeLexToColumnType(CODE_LEX token);
ColumnDirectiveToken mapCodeLexToColumnDirectiveToken(CODE_LEX token);

//for debugging

void printTable(Table table);
void printTableDirectives(Table table);
void printColumns(Table table);
void printColumnDirectives(Column column);
void printColumnDirectiveArguments(ColumnDirective columnDirective);



#endif
