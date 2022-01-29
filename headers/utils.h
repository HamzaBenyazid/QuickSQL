#ifndef UTILS_H_
#define UTILS_H_

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"data.h"
#include"sem.h"

void initTablesAndViewsAndIndexes();

void addTableName(char* tableName);
void addTableDirective(Type tableDirective);
void addTableDirectiveArgument(char* argument);
void addColumnName(char* columnName);
void addColumnType(Type type);
void addVCLength(char* length);
void addColumnDirective(Type columnDirective);
void addColumnDirectiveArgument(char* argument);
void addViewName(char* viewName);
void addViewTableName(char* tableName);
void addComment(char* comment);
void addIndex();
Table getTable(char* name);
int tableExists(char* name);

void freeTablesAndViewsAndIndexes();

ColumnType mapCodeLexToColumnType(Type token);
ColumnDirectiveToken mapCodeLexToColumnDirectiveToken(Type token);
int a2i(char* s);
char* i2a(int num, char* buffer, int base);

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
