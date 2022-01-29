#ifndef UTILS_H
#define UTILS_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"data.h"
#include"lex.h"
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
void addIndex();
Table getTable(char* name);
int tableExists(char* name);

void freeTablesAndViews();

ColumnType mapCodeLexToColumnType(Type token);
ColumnDirectiveToken mapCodeLexToColumnDirectiveToken(Type token);
int a2i(char* s);

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
