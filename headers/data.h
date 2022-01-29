#ifndef DATA_H
#define DATA_H

#define MAX_NUM_CD 8
#define MAX_NUM_TD 2
#define MAX_NAME_LEN 128
#define MAX_TAB_SIZE 10
#define MAX_VIEWS_SIZE 10
#define MAX_INDEXES_SIZE 10
#define MAX_COL_SIZE 100
#define MAX_CD_ARGS 10
#define MAX_VIEW_TABS 10

#include <stdio.h>
#include<stdlib.h>
#include<math.h>

typedef enum
{
	// valid table, view,comlumn name
	TOKEN_ID,
	TOKEN_NL,
	TOKEN_VIEW,
	TOKEN_TD_SELECT,
	TOKEN_TD_COLPREFIX,
	TOKEN_NUM,
	TOKEN_INT,
	TOKEN_D,
	TOKEN_TS,
	TOKEN_TSTZ,
	TOKEN_VC,
	TOKEN_VCNNN,
	TOKEN_CLOB,
	TOKEN_BLOB,
	TOKEN_JSON,
	TOKEN_PK,
	TOKEN_FK,
	TOKEN_CHECK,
	TOKEN_NN,
	TOKEN_BETWEEN,
	TOKEN_INDEX,
	TOKEN_DEFAULT,
	TOKEN_UNIQUE,
	// string between '' quotes
	TOKEN_STRING,
	// litteral number: 344,4 ,56 hhhhh
	TOKEN_NUMBER,
	TOKEN_COMMENT,
	TOKEN_COMMA,
	TOKEN_EOF,
	TOKEN_ERR,
	TOKEN_WHITESPACE
} Type;
typedef struct
{
	Type type;
	char *value;
} Token;

typedef struct
{
	char c;

} Lexer;
Lexer *lexer;
Token *token;
Token *Putback_token;
FILE *inputFile;
extern int Lines ;
extern int Columns ;
int Putback;
Token **tokens;

typedef enum {
    PK_TOKEN,
    FK_TOKEN,
    CHECK_TOKEN,
    NN_TOKEN,
    BETWEEN_TOKEN,
    INDEX_TOKEN,
    DEFAULT_TOKEN,
    UNIQUE_TOKEN
}ColumnDirectiveToken;

typedef enum {
    NUM,
    INT,
    D,
    TS,
    TSTZ,
    VC,
    VCNNN,
    CLOB,
    BLOB,
    JSON,
} ColumnType;

typedef enum {
    COLPREFIX_TOKEN,
    SELECT_TOKEN
} TableDirectiveToken;

typedef struct{
    ColumnDirectiveToken token;
    char** arguments;
    int numberOfArgs;
}ColumnDirective;

typedef struct{
    char name[MAX_NAME_LEN];
    ColumnType type;
    int vcnnn;
    ColumnDirective columnDirectives[MAX_NUM_CD];
    int numberOfCD; //number of column directives
    char* comment;
} Column;

typedef struct{
    TableDirectiveToken token;
    char* argument;
}TableDirective;

typedef struct{
    char name[MAX_NAME_LEN];
    TableDirective tableDirectives[MAX_NUM_TD];
    int numberOfTD;
    Column* columns;
    int numberOfColumns;
    char* comment;
}Table;

typedef struct{
    char name[MAX_NAME_LEN];
    char** tableNames;
    int numberOfTableNames;
}View;
typedef struct{
    char tableName[MAX_NAME_LEN];
    char columnName[MAX_NAME_LEN];
}Index;

Table* tables;
View* views;
Index* indexes;

int numberOfTables;
int numberOfViews;
int numberOfIndexes;

#endif