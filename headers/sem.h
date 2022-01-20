#ifndef SEM_H
#define SEM_H

typedef enum {
    PK_TOKEN,
    FK_TOKEN,
    CHECK_TOKEN,
    NN_TOKEN,
    BETWEEN_TOKEN,
    INDEX_TOKEN,
    DEFAULT_TOKEN
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
}ColumnDirective;

typedef struct{
    char* name;
    ColumnType type;
    ColumnDirective* columnDirectives;
} Column;
typedef struct{
    TableDirectiveToken token;
    char* argument;
}TableDirective;
typedef struct{
    char* name;
    TableDirective* tableDirectives;
    Column* columns;
}Table;

Table* tables;

#endif