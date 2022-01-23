#ifndef UTILS_H
#define UTILS_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"data.h"
#include"lex.h"
#include"sem.h"

void initTablesAndViews();

void addTableName(char* tableName);
void addTableDirective(CODE_LEX tableDirective);
void addTableDirectiveArgument(char* argument);
void addColumnName(char* columnName);
void addColumnType(CODE_LEX type);
void addColumnDirective(CODE_LEX columnDirective);
void addColumnDirectiveArgument(char* argument);
void addViewName(char* viewName);
void addViewTableName(char* tableName);

void freeTablesAndViews();

ColumnType mapCodeLexToColumnType(CODE_LEX token);
ColumnDirectiveToken mapCodeLexToColumnDirectiveToken(CODE_LEX token);

//for debugging

void printTable(Table table);
void printTableDirectives(Table table);
void printColumns(Table table);
void printColumnDirectives(Column column);
void printColumnDirectiveArguments(ColumnDirective columnDirective);
void printView(View view);
void printViewTableNames(View view);
void printTablesAndViews();

#endif
