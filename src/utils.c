#include"../headers/utils.h"

int numberOfTables;
int numberOfViews;

void initTablesAndViewsAndIndexes(){
    tables = malloc(MAX_TAB_SIZE*sizeof(Table));
    numberOfTables = 0;
    views = malloc(MAX_VIEWS_SIZE*sizeof(View));
    numberOfViews = 0;
    indexes = malloc(MAX_INDEXES_SIZE*sizeof(Index));
    numberOfIndexes=0;
}
void freeTablesAndViews(){
    for(int i=0;i<numberOfTables;i++){
        free(tables[i].columns);
    }
    free(tables);
    for(int i=0;i<numberOfViews;i++){
        free(views[i].tableNames);
    }
    free(views);
}
void addTableName(char* tableName){
    checkNameLength(tableName);
    if(numberOfTables==MAX_TAB_SIZE){
        //re-allocating
        tables = realloc(tables,MAX_TAB_SIZE*sizeof(Table));
    }
    Table table;
    strcpy(table.name,tableName);
    table.columns = malloc(MAX_COL_SIZE*sizeof(Column));
    table.numberOfColumns=0;
    table.numberOfTD=0;
    *(tables+numberOfTables)=table;
    numberOfTables++;
}
void addTableDirective(Type tableDirectivetoken){
    Table table = *(tables+numberOfTables-1);
    TableDirective tableDirective;
    if(tableDirectivetoken==TOKEN_TD_COLPREFIX){
        tableDirective.token=COLPREFIX_TOKEN;
    }else if(tableDirectivetoken==TOKEN_TD_SELECT){
        tableDirective.token=SELECT_TOKEN;
    }else{
        printf("Warning : this is not a table directive token");
    }
    int numberOfTD = table.numberOfTD;
    *(table.tableDirectives+numberOfTD)=tableDirective;
    table.numberOfTD++;
    *(tables+numberOfTables-1) = table;
}
void addTableDirectiveArgument(char* argument){
    Table table = *(tables+numberOfTables-1);
    TableDirective tableDirective;
    strcpy(tableDirective.argument,argument);
    int numberOfTD = table.numberOfTD;
    *(table.tableDirectives+numberOfTD)=tableDirective;
    *(tables+numberOfTables-1) = table;
}
void addColumnName(char* columnName){
    checkNameLength(columnName);
    Table table=*(tables+numberOfTables-1);
    int numberOfColumns=table.numberOfColumns;
    if(numberOfColumns==MAX_COL_SIZE){
        //re-allocating
        table.columns=realloc(table.columns,MAX_COL_SIZE*sizeof(Column));
    }
    Column column;
    //initializing column fields
    strcpy(column.name,columnName);
    column.numberOfCD=0;
    column.type=-1;
    //saving
    *(table.columns+numberOfColumns)=column;
    table.numberOfColumns++;
    *(tables+numberOfTables-1)=table;
}

void addColumnType(Type type){
    ColumnType columnType = mapCodeLexToColumnType(type);
    Table table=tables[numberOfTables-1];
    int numberOfColumns=table.numberOfColumns;
    Column column=table.columns[numberOfColumns-1];
    column.type=columnType;
    table.columns[numberOfColumns-1]=column;
    tables[numberOfTables-1]=table;
}
void addVCLength(char* length){
    Table table=tables[numberOfTables-1];
    int numberOfColumns=table.numberOfColumns;
    Column column=table.columns[numberOfColumns-1];
    column.vcnnn = a2i(length);
    table.columns[numberOfColumns-1]=column;
    tables[numberOfTables-1]=table;
}
void addColumnDirective(Type columnDirective){
    Table table = *(tables+numberOfTables-1);
    int numberOfColumns=table.numberOfColumns;
    Column column = *(table.columns+numberOfColumns-1);
    ColumnDirectiveToken token=mapCodeLexToColumnDirectiveToken(columnDirective);
    ColumnDirective directive;
    directive.token=token;
    directive.numberOfArgs=0;
    int numberOfCD=column.numberOfCD;
    *(column.columnDirectives+numberOfCD)=directive;
    column.numberOfCD++;
    *(table.columns+numberOfColumns-1)=column;
    *(tables+numberOfTables-1)=table;
}
void addColumnDirectiveArgument(char* argument){
    Table table = *(tables+numberOfTables-1);
    int numberOfColumns=table.numberOfColumns;
    Column column = *(table.columns+numberOfColumns-1);
    int numberOfCD = column.numberOfCD;
    ColumnDirective columnDirective = *(column.columnDirectives+numberOfCD-1);
    int numberOfArgs = columnDirective.numberOfArgs;
    if(numberOfArgs==0){
        columnDirective.arguments= (char**)malloc(1*sizeof(char*));
    }else{
        columnDirective.arguments=realloc(columnDirective.arguments,1*sizeof(argument));
    }
    columnDirective.arguments[numberOfArgs] = malloc(1*sizeof(argument));
    strcpy(columnDirective.arguments[numberOfArgs],argument);
    columnDirective.numberOfArgs++;
    *(column.columnDirectives+numberOfCD-1)=columnDirective;
    *(table.columns+numberOfColumns-1)=column;
    *(tables+numberOfTables-1)=table;
}
void addViewName(char* viewName){
    checkNameLength(viewName);
    if(numberOfViews==MAX_VIEWS_SIZE){
        //re-allocating
        views = realloc(views,MAX_VIEWS_SIZE*sizeof(View));
    }
    View view;
    strcpy(view.name,viewName);
    view.tableNames = malloc(MAX_VIEW_TABS*sizeof(char*));
    view.numberOfTableNames=0;
    views[numberOfViews]=view;
    numberOfViews++;
}
void addViewTableName(char* tableName){
    if(strlen(tableName)>MAX_NAME_LEN){
        printf("\nSemantic error : table name must not exceed 128 characters.\n");
        exit(EXIT_FAILURE);
    }
    View view = views[numberOfViews-1];
    int numberOfTabNames=view.numberOfTableNames;
    if(numberOfTabNames==MAX_VIEW_TABS){
        //re-allocating
        view.tableNames = realloc(view.tableNames,MAX_VIEW_TABS*sizeof(char*));
    }
    view.tableNames[numberOfTabNames]=malloc(MAX_NAME_LEN*sizeof(char));
    strcpy(view.tableNames[numberOfTabNames],tableName);
    view.numberOfTableNames++;
    views[numberOfViews-1]=view;
}
void addIndex(){
    if(numberOfIndexes==MAX_INDEXES_SIZE){
        indexes = realloc(indexes,MAX_INDEXES_SIZE*sizeof(Index));
    }
    Table table = tables[numberOfTables-1];
    Column column = table.columns[table.numberOfColumns-1];
    Index index;
    strcpy(index.tableName,table.name);
    strcpy(index.columnName,column.name);
    indexes[numberOfIndexes]=index;
    numberOfIndexes++;
}

ColumnType mapCodeLexToColumnType(Type token){
    return (ColumnType)(token-TOKEN_NUM);
}
ColumnDirectiveToken mapCodeLexToColumnDirectiveToken(Type token){
    return (ColumnDirectiveToken)(token-TOKEN_PK);
}
int a2i(char* s){
  int sign=1;
  if(*s == '-'){
    sign = -1;
    s++;
  }
  int num=0;
  while(*s){
    num=((*s)-'0')+num*10;
    s++;   
  }
  return num*sign;
}
void printTable(Table table){
    printf("Table : \n");
    printf("\tname : %s \n",table.name);
    printTableDirectives(table);
    printColumns(table);
}
void printTableDirectives(Table table){
    TableDirective tableDirective;
    printf("\tTableDirectives :\n");
    for(int i=0;i<table.numberOfTD;i++){
        tableDirective = *(table.tableDirectives+i);
        if(tableDirective.token==SELECT_TOKEN){
            printf("\t\tTD : \\select\n");
        }
        if(tableDirective.token==COLPREFIX_TOKEN){
            printf("\t\tTD : \\colprefix\n");
            if(tableDirective.argument!=NULL){
                printf("\t\t\targ : %s\n",tableDirective.argument);
            }
        }
        printf("\n");
    }
}
void printColumns(Table table){
    printf("\tcolumns :\n");
    Column column; 
    for(int i=0;i<table.numberOfColumns;i++){
        column = *(table.columns+i);
        printf("\t\tname :%s\n",column.name);
        printf("\t\ttype :");
        if(column.type!=-1) printf("%d\n",column.type); 
        else printf("null\n");
        if(column.numberOfCD>0)
            printColumnDirectives(column);
        printf("\n");
    }

}
void printColumnDirectives(Column column){
    printf("\t\tcolumnDirectives :\n");
    ColumnDirective columnDirective;
    for(int i=0;i<column.numberOfCD;i++){
        columnDirective = *(column.columnDirectives+i);
        printf("\t\t\t CD: %d\n",columnDirective.token);
        printColumnDirectiveArguments(columnDirective);
        printf("\n");
    }
}
void printColumnDirectiveArguments(ColumnDirective columnDirective){
    printf("\t\t\t arguments : ");
    char* argument;
    for(int i=0;i<columnDirective.numberOfArgs;i++){
        argument=columnDirective.arguments[i];
        printf("%s,",argument);
    }
    printf("\n");
}
void printView(View view){
    printf("View : \n");
    printf("\tname : %s \n",view.name);
    printViewTableNames(view);
}
void printViewTableNames(View view){
    printf("\tTable names :");
    for(int i=0;i<view.numberOfTableNames;i++){
        printf(" %s,",view.tableNames[i]);
    }
    printf("\n");
}
void printTablesAndViews(){
    Table table;
    View view;
    for(int i=0;i<numberOfTables;i++){
        table = tables[i];
        printTable(table);
    }
    for(int i=0;i<numberOfViews;i++){
        view = views[i];
        printView(view);
    }
}
// void main(){

//     initTablesAndViews();

//     addTableName("table1");
//     addTableDirective(TOKEN_TD_SELECT);
//     addColumnName("col1");
//     addColumnType(TOKEN_INT);
//     addColumnDirective(TOKEN_BETWEEN);
//     addColumnDirectiveArgument("2");
//     addColumnDirectiveArgument("10");
//     addColumnName("col2");
//     addColumnType(TOKEN_TS);
//     addColumnDirective(TOKEN_UNIQUE);
//     addViewName("view1");
//     addViewTableName("table1");
//     addViewTableName("table2");

//     printTablesAndViews();
// }

