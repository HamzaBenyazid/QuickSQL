#include "../headers/toSQL.h"


void putString(char* s){
    fputs(s,sqlFile);
}
void putInt(int n){
    char s[20];
    sprintf(s,"%d",n);
    fputs(s,sqlFile);
}
int isPrimaryKey(Column column){
    ColumnDirective columnDirective;
    for(int i=0;i<column.numberOfCD;i++){
        columnDirective = column.columnDirectives[i];
        if(columnDirective.token==PK_TOKEN){
            return 1;
        }
    }
    return 0;
}
int isForeightKey(Column column){
    ColumnDirective columnDirective;
    for(int i=0;i<column.numberOfCD;i++){
        columnDirective = column.columnDirectives[i];
        if(columnDirective.token==FK_TOKEN){
            return 1;
        }
    }
    return 0;
}

int hasPrimaryKey(Table table){
    Column column;
    for(int i=0;i<table.numberOfColumns;i++){
        column = table.columns[i];
        if(isPrimaryKey(column)) 
            return 1;
    }
    return 0;
}

void generateSQL(char* fileName){
    char* fileNameWithExtention = malloc(strlen(fileName)+strlen(".sql"));
    strcpy(fileNameWithExtention,fileName);
    strcat(fileNameWithExtention,".sql"); 
    sqlFile = fopen(fileNameWithExtention,"w");
    generateTables();
    generateIndexes();
    generateViews();
    generateSelectquerys();
    fclose(sqlFile);
    freeTablesAndViewsAndIndexes();
}

void generateTables(){
    putString("-- create tables\n");
    for(int i=0;i<numberOfTables;i++){
        generateTable(tables[i]);
    }
    putString("\n");
}

void generateTable(Table table){
    putString("create table ");
    putString(table.name);
    putString(" (\n");
    int index;
    if((index=colPrefixTDIndex(table))!=-1)
        table = addColPrefix(table,index);
    generateColumns(table);
    putString(")\n;\n\n");

    if(table.comment!=NULL) {
        generateTableComment(table);
        generateColumnsComment(table,1);
    }else{
        generateColumnsComment(table,0);
    }
}
int colPrefixTDIndex(Table table){
    TableDirective tableDirective;
    for(int i=0;i<table.numberOfTD;i++){
        tableDirective = table.tableDirectives[i];
        if(tableDirective.token==COLPREFIX_TOKEN)
            return i;
    }
    return -1;
}
Table addColPrefix(Table table,int index){
    char columnName[MAX_NAME_LEN];
    for(int i=0;i<table.numberOfColumns;i++){
        strcpy(columnName,table.columns[i].name);
        strcpy(table.columns[i].name,table.tableDirectives[index].argument);
        strcat(table.columns[i].name,"_");
        strcat(table.columns[i].name,columnName);
    }
    return table;
}
void generateColumns(Table table){
    Column column;
    int isLastCol;
    if(!hasPrimaryKey(table))
        generateColumn(table.name,(Column){"id",-1,0,{PK_TOKEN},2,NULL},0);
    for(int i=0;i<table.numberOfColumns;i++){
        column = table.columns[i];

        if(i==table.numberOfColumns-1)
            isLastCol=1;
        else
            isLastCol=0;

        generateColumn(table.name,column,isLastCol);
    }
}
void generateTableComment(Table table){
    //comment on table user1 is 'hhh';
    putString("--comments\n");
    putString("comment on table ");
    putString(table.name);
    putString(" is '");
    putString(table.comment);
    putString("';\n");
}
void generateColumnsComment(Table table,int hasTableComment){
    Column column;
    int isFirstComment=1;
    for(int i=0;i<table.numberOfColumns;i++){
        column = table.columns[i];
        //comment on column user1.col1 is 'comment';
        if(column.comment!=NULL){
            if(!hasTableComment && isFirstComment){
                putString("--comments\n");
                isFirstComment=0;
            }
            putString("comment on column ");
            putString(table.name);
            putString(".");
            putString(column.name);
            putString(" is '");
            putString(column.comment);
            putString("';\n");
        }
    }
    if(isFirstComment && hasTableComment)
        putString("\n");
}
void generateColumn(char* tableName,Column column,int isLastCol){
    putString("\t");
    putString(column.name);
    putString("\t\t");
    if(isPrimaryKey(column)){
        putString("number generated by default on null as identity");
    }
    else if(isForeightKey(column)){
        putString("number");
    }
    else{
        switch(column.type){
            case NUM : putString("number");break;
            case INT : putString("integer");break;
            case D : putString("date");break;
            case TS : putString("timestamp");break;
            case TSTZ : putString("timestamp with time zone");break;
            case VC : putString("varchar(4000 char)");break;
            case VCNNN : 
                putString("varchar(");
                if(column.vcnnn<4000) putInt(column.vcnnn);
                else putInt(4000);
                putString(" char)");
                break;
            case CLOB : putString("clob");break;
            case BLOB : putString("blob");break;
            case JSON : 
                putString("clob check ()");
                putString(column.name);
                putString(" is json)");
                break;
            default : putString("varchar(4000 char)");
        }
    }
    generateConstraints(tableName,column);
    if(!isLastCol) putString(",");
    putString("\n");
}
void generateConstraints(char* tableName,Column column){
    ColumnDirective columnDirective;
    for(int i=0;i<column.numberOfCD;i++){
        columnDirective = column.columnDirectives[i];
        if(columnDirective.token!=INDEX_TOKEN)
            generateConstraint(tableName,column.name,columnDirective);
    }
}

void generateConstraint(char* tableName,char* columnName,ColumnDirective columnDirective){
    putString(" constraint ");
    putString(tableName);
    putString("_");
    putString(columnName);
    putString("_");
    switch(columnDirective.token){
        case PK_TOKEN :
            putString("pk primary key");
            break;
        case FK_TOKEN : 
            putString("fk ");
            putString("references ");
            putString(columnDirective.arguments[0]);
            putString(" on delete cascade");
            break;
        case CHECK_TOKEN :
            putString("cc");
            //check (col2 in ('1','2'))
            putString(" check (");
            putString(columnName);
            putString(" in (");
            for(int i=0;i<columnDirective.numberOfArgs;i++){
                putString("'");
                putString(columnDirective.arguments[i]);
                putString("'");
                if(i!=columnDirective.numberOfArgs-1)
                    putString(",");
            }
            putString("))");
            break;
        case NN_TOKEN :
            putString("nn");
            putString(" not null");
        case BETWEEN_TOKEN :
            //check (col2 between a and b)
            putString("bet");
            putString(" check (");
            putString(columnName);
            putString("between ");
            putString(columnDirective.arguments[0]);
            putString(" and ");
            putString(columnDirective.arguments[1]);
            putString(")");
            break;
        case DEFAULT_TOKEN :
            putString("df");
            putString(" default on null ");
            putString(columnDirective.arguments[0]);
            break;
        case UNIQUE_TOKEN :
            putString("unq");
            putString(" unique");
            break;
    }
}
void generateIndexes(){
    putString("-- table index\n");
    for(int i=0;i<numberOfIndexes;i++){
        generateIndex(indexes[i],i+1);
    }
    putString("\n");
}
void generateIndex(Index index,int indexNumber){
    /*create index user2_i1 on user2 (col1);*/
    putString("create index ");
    putString(index.tableName);
    putString("_");
    putInt(indexNumber);
    putString(" on ");
    putString(index.tableName);
    putString(" (");
    putString(index.columnName);
    putString(");\n");
}
void generateViews(){
    putString("-- create views\n");
    for(int i=0;i<numberOfViews;i++){
        generateView(views[i]);
    }
}
void generateView(View view){
    Table table;
    Column column;
    putString("create or replace view ");
    putString(view.name);
    putString(" as \nselect\n");
    for(int i=0;i<view.numberOfTableNames;i++){
        table=getTable(view.tableNames[i]);
        for(int j=0;j<table.numberOfColumns;j++){
            column = table.columns[j];
            putString("\t");
            putString(table.name);
            putString(".");
            putString(column.name);
            putString("\t\t\t\t\t\t");
            putString(table.name);
            putString("_");
            putString(column.name);
            if(i!=view.numberOfTableNames-1 || j!=table.numberOfColumns-1)
                putString(",");
            putString("\n");
        }
    }
    putString("from \n");
    for(int i=0;i<view.numberOfTableNames;i++){
        putString("\t");
        putString(view.tableNames[i]);
        if(i!=view.numberOfTableNames-1)
            putString(",");   
    }
    putString("\nwhere \n\n/\n\n");

}
void generateSelectquerys(){
    Table table;
    putString("-- load data\n");
    for(int i=0;i<numberOfTables;i++){
        table=tables[i];
        if(hasSelectDirective(table))
            generateSelectquery(table);
    }
}
void generateSelectquery(Table table){
    putString("select\n");
    for(int i=0;i<table.numberOfColumns;i++){
        putString("\t");
        putString(table.columns[i].name);
        if(i!=table.numberOfColumns-1)
            putString(",");
        putString("\n");
    }
    putString("from ");
    putString(table.name);
    putString(";\n\n");
}
int hasSelectDirective(Table table){
    for(int i=0;i<table.numberOfTD;i++){
        if(table.tableDirectives[i].token==SELECT_TOKEN)
            return 1;
    }
    return 0;
}
// void main(){
//     initTablesAndViewsAndIndexes();
//     addTableName("table1");
//     addTableDirective(TOKEN_TD_SELECT);
//     addColumnName("col1");
//     addColumnType(TOKEN_D);
//     addColumnDirective(TOKEN_CHECK);
//     addColumnDirectiveArgument("12-10-2022");
//     addColumnDirectiveArgument("12-10-2023");
//     addColumnName("col2");
//     addColumnDirective(TOKEN_FK);
//     addColumnDirectiveArgument("table2");
//     addTableName("table2");
//     addColumnName("col1");
//     addColumnDirective(TOKEN_INDEX);
    
//     addViewName("view1");
//     addViewTableName("table1");
//     addViewTableName("table2");
//     generateSQL("file1");
// }