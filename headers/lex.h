#if !defined(LEX_H_)
#define LEX_H_


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
	enum
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
		TOKEN_FK,
		TOKEN_CHECK,
		TOKEN_NN,
		TOKEN_UNIQUE,
		TOKEN_BETWEEN,
		TOKEN_INDEX,
		TOKEN_DEFAULT,
		TOKEN_PK,
		// string between '' quotes
		TOKEN_STRING,
		// litteral number: 344,4 ,56 hhhhh
		TOKEN_NUMBER,
		TOKEN_COMMENT,
		TOKEN_COMMA,
		TOKEN_EOF,
		TOKEN_ERR,
		TOKEN_WHITESPACE
	} type;
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
int Lines = 1;
int Columns = 0;
int Putback;
Token **tokens;
// prototypes
void skip_whitespace();
void get_next_cat();
void lexer_init();
void get_next_car();
Token *token_init(int type, char *value);
char *lexer_get_caracter_as_string();
void lexer_putback();
char *lexer_get_string();
Token *lexer_get_next_token();
void lexer_scan_file();
void skip_whitespace();


#endif