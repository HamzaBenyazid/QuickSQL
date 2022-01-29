#include<stdio.h>
#include<stdlib.h>
#include"../headers/data.h"
#include"../headers/lex.h"
#include"../headers/parser.h"
#include"../headers/sem.h"
#include"../headers/toSQL.h"


int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("Please insert all requierements to compile the program");
		exit(1);
	}
	if ((inputFile = fopen(argv[1], "r")) == NULL)
	{
		printf("Could not open the folder");
		exit(1);
	}
	lexer_init();
    parse();
    sem();
    generateSQL(argv[2]);
	return 0;
}