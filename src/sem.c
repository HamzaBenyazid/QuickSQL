#include"../headers/sem.h"
#include "../headers/utils.h"

void sem(){
    checkTableNamesDeclarations();
    checkColumnNamesDeclarations();
    checkTableDirectives();
    checkColumnDirectives();

}

void checkTableNamesDeclarations(){
    int i,j;
    Table table1,table2;
    for(i=0;i<numberOfTables;i++){
        table1=tables[i];
        for(j=i+1;j<numberOfTables;j++){
            table2=tables[j];
            if(strcmp(table1.name,table2.name)==0){
                printf("\nSemantic error : table names must be unique\n");
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
        table = tables[i];
        numberOfColumns=table.numberOfColumns;
        for(j=0;j<numberOfColumns;j++){
            column1 = table.columns[j];
            for(k=j+1;k<numberOfColumns;k++){
                column2 = table.columns[k];
                if(strcmp(column1.name,column2.name)==0){
                    printf("\nSemantic error :column names must be unique\n");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
}
void checkTableDirectives(){
    Table table;
    int i;
    for(i=0;i<numberOfTables;i++){
        table = tables[i];
        if(table.numberOfTD==2){
            if(table.tableDirectives[0].token==table.tableDirectives[1].token){
                printf("\nSemantic Error : table directive must not be used more than one time in a table\n");
                exit(EXIT_FAILURE);
            }
        }   
    }
}
void checkColumnDirectives(){
    Table table;
    Column column;
    int i,j,k,l;
    int numberOfCD ;
    for(i=0;i<numberOfTables;i++){
        table = tables[i];
        for(j=0;j<table.numberOfColumns;j++){
            column = table.columns[j];
            numberOfCD= column.numberOfCD;
            for(k=0;k<numberOfCD;k++){
                for(l=k+1;k<numberOfCD;l++){
                    if(column.columnDirectives[k].token==column.columnDirectives[l].token){
                        printf("\nSemantic error : column directive must not be used more than one time in a column\n");
                        exit(EXIT_FAILURE);
                    }
                }
            }
        } 
    }
}
void checkNameLength(char* name){
    if(strlen(name)>MAX_NAME_LEN){
        printf("\nSemantic error : table,column and view name must not exceed 128 characters.\n");
        exit(EXIT_FAILURE);
    }
}
void main(){
    initTablesAndViews();


    //remove comment from one part to test every rule separately 


    // //testing rule 1
    // addTableName("rule1");
    // addTableName("rule1");
    // printTablesAndViews();
    // checkTableNamesDeclarations();

    // //testing rule 2
    // addTableName("rule2");
    // addColumnName("col1");
    // addColumnName("col1");
    // printTablesAndViews();
    // checkColumnNamesDeclarations();

    // //testing rule 3
    // addTableName("rule3");
    // addTableDirective(TOKEN_TD_SELECT);
    // addTableDirective(TOKEN_TD_SELECT);
    // printTablesAndViews();
    // checkTableDirectives();

    // //testing rule 4
    // addTableName("rul4");
    // addColumnName("col1");
    // addColumnDirective(TOKEN_BETWEEN);
    // addColumnDirective(TOKEN_BETWEEN);
    // printTablesAndViews();
    // checkColumnDirectives();

    // //testing rule 5
    // addTableName("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque libero velit, ultricies eu iaculis ac, malesuada a urna sed.");

    freeTablesAndViews();
}