#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../headers/lex.h"

Token *token;

void lexer_init(){
	token = calloc(1, sizeof(Token));
    lexer=calloc(1,sizeof(Lexer));
}
void get_next_car()
{
    if (Putback)
	{
		lexer->c = Putback;
		Putback = 0;
		return;
	}
    lexer->c=fgetc(inputFile);
}

Token *token_init(CODE_LEX code, char *value)
{
	token->code = code;
	token->value = value;
	return token;
}
char *lexer_get_caracter_as_string()
{
	char *c = calloc(2, sizeof(char));
	c[0] = lexer->c;
	c[1] = '\0';
	return c;
}
void lexer_putback()
{
    Putback = lexer->c;
}
char *lexer_get_string()
{
	get_next_car();

	char *value = calloc(1, sizeof(char));
	value[0] = '\0';

	while (lexer->c != ' ')
	{
		char *s = lexer_get_caracter_as_string();
		value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
		strcat(value, s);
		get_next_car();
	}

	get_next_car();
	return value;
}
Token* lexer_get_next_token(){
        skip_whitespace();
        switch(lexer->c){
            case ',':
                    return token_init(TOKEN_COMMA,lexer_get_caracter_as_string());
                    break;
            case '\n':
                    return token_init(TOKEN_NL,lexer_get_caracter_as_string());
                    break;
            case ' ':
                    return token_init(TOKEN_WHITESPACE,lexer_get_caracter_as_string());
                    break;
            case '[':
                    return token_init(TOKEN_OPN_BRCKT,lexer_get_caracter_as_string());
                    break;
            case ']':
                    return token_init(TOKEN_CLS_BRCKT,lexer_get_caracter_as_string());
                    break;
            case 'd':
                    return token_init(TOKEN_D,lexer_get_caracter_as_string());
                    break;
            case EOF :
                    return token_init(TOKEN_EOF,"EOF");
                    break;
            default:{
         if (lexer->c == '-')
		{
			char *value = calloc(1, sizeof(char));
			value[0] = lexer->c;
			get_next_car();
			if (lexer->c == '-')
			{
				char *s = lexer_get_caracter_as_string();
				value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
				strcat(value, s);
				return token_init(TOKEN_DOUBLE_HYPHEN, value);
			}
			free(value);
			lexer_putback();
		}
        if (lexer->c == 't')
		{
			char *value = calloc(1, sizeof(char));
			value[0] = lexer->c;
			get_next_car();
			if (lexer->c == 's')
			{
				char *s = lexer_get_caracter_as_string();
				value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
				strcat(value, s);
				return token_init(TOKEN_TS, value);
			}
			free(value);
			lexer_putback();
		}
        if (lexer->c == 'v')
		{
			char *value = calloc(1, sizeof(char));
			value[0] = lexer->c;
			get_next_car();
			if (lexer->c == 'c')
			{
				char *s = lexer_get_caracter_as_string();
				value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
				strcat(value, s);
				return token_init(TOKEN_VC, value);
			}
			free(value);
			lexer_putback();
		}
        if (lexer->c == '/')
		{   //table directives
            char* directive = lexer_get_string();
            if(strcmp(directive,"select")==0) return token_init(TOKEN_TD_SELECT,strcat("/",directive));
		}


            }



    }

}
void lexer_scan_file(){
    lexer_init();

	while (!feof(inputFile))
	{
		Token *token = lexer_get_next_token();
		printf("< %s > \n", token->value);
	}
}
void skip_whitespace(){

	get_next_car();
    //int fseeked=0;
	while (lexer->c == '\b' || lexer->c == '\r' || lexer->c == '\f' ||lexer->c == ' ' )
	{
        // if(lexer->c == ' ' ){
        //     int cpt=0;
        //     while(lexer->c==' '){
        //         get_next_car();
        //         cpt++;
        //     }

        //     if(lexer->c !='\n' && fseeked==0 ){
        //       //rollback
        //       fseek(inputFile,-cpt, SEEK_CUR);
        //       fseeked=1;
        //       printf("rah rje3");
        //     }

        // }
        // else get_next_car();

        get_next_car();
	}


}
int main(int argc, char *argv[]){
    if (argc != 2)
	{
		printf("Please insert all requierements to compile the program");
		exit(1);
	}
	if ((inputFile = fopen(argv[1], "r")) == NULL)
	{
		printf("Could not open the folder");
		exit(1);
	}

    lexer_scan_file();
    return 0;
}
