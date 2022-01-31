#ifndef TO_SQL_H_
#define TO_SQL_H_

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "data.h"
#include "utils.h"

void generateSQL();
void generateTables();
void generateIndexes();
void generateViews();
void generateSelectquerys();
void generateSelectquery(Table table);
int hasSelectDirective(Table table);
void generateTable(Table table);
void generateIndex(Index index,int indexNumber);
void generateView(View view);
void generateColumns(Table table);
void generateColumn(char* tableName,Column column,int isLastCol);
void generateConstraints(char* tableName,Column column);
void generateConstraint(char* tableName,char* columnName,ColumnDirective columnDirective);
void generateColumnsComment(Table table,int hasTableComment);
void generateTableComment(Table table);
int colPrefixTDIndex(Table table);
Table addColPrefix(Table table,int index);

int hasPrimaryKey(Table table);
int isPrimaryKey(Column column);
int isForeightKey(Column column);

void putString();
void putInt();

FILE* sqlFile;

#endif