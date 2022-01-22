#include"../headers/sem.h"

void sem(){
    numberOfTables = countNumberOfTables();
    numberOfViews = countNumberOfViews();
    checkTableNamesDeclarations();
    checkColumnNamesDeclarations();
}
int countNumberOfTables(){
    Table table = *tables;
    int i=0;
    while(table.name!=NULL){
        i++;
        table = *(tables+i);
    }
    return i;
}
int countNumberOfViews(){
    View view = *views;
    int i=0;
    while(view.name!=NULL){
        i++;
        view = *(views+i);
    }
    return i;

}
int countNumberOfColumns(Table table){
    int i=0;
    Column column = *(table.columns);
    while(column.name!=NULL){
        i++;
        column = *(table.columns+i);
    }
    return i;
}
void checkTableNamesDeclarations(){
    int i,j;
    Table table1,table2;
    for(i=0;i<numberOfTables;i++){
        table1=*(tables+i);
        for(j=i+1;j<numberOfTables;j++){
            table2=*(tables+j);
            if(strcmp(table1.name,table2.name)==0){
                printf("table names must be unique");
                exit(EXIT_FAILURE);
            }
        }
    }
}
void checkColumnNamesDeclarations(){
    int i,j,k;
    int numberOfColumns;
    Table table;
    Column column1,column2;
    for(i=0;i<numberOfTables;i++){
        table = *(tables+i);
        numberOfColumns=countNumberOfColumns(table);
        for(j=0;j<numberOfColumns;j++){
            column1 = *(table.columns+j);
            for(k=j+1;k<numberOfColumns;k++){
                column2 = *(table.columns+k);
                if(strcmp(column1.name,column2.name)==0){
                    printf("column names must be unique");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
}
void checkTableDirectives(){
    int i;
    int numberOfTableDirectives;
    Table table;

    for(i=0;i<numberOfTables;i++){
        table = *(tables+i);
        countNumberOfTableDirectives(table);
    }
}