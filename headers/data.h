#ifndef DATA_H
#define DATA_H

#define MAX_NUM_CD 8
#define MAX_NUM_TD 2
#define MAX_NAME_LEN 128
#define MAX_TAB_SIZE 10
#define MAX_VIEWS_SIZE 10
#define MAX_COL_SIZE 100
#define MAX_CD_ARGS 10
#define MAX_VIEW_TABS 10


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
    ColumnDirective columnDirectives[MAX_NUM_CD];
    int numberOfCD; //number of column directives
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
}Table;

typedef struct{
    char name[MAX_NAME_LEN];
    char** tableNames;
    int numberOfTableNames;
}View;

Table* tables;
View* views;

int numberOfTables;
int numberOfViews;

#endif