#if !defined(LEX_H_)
#define LEX_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

extern char *token_str[];
// prototypes
void skip_whitespace();
void get_next_cat();
void lexer_init();
void get_next_car();
Token *token_init(int type, char *value);
char *lexer_get_caracter_as_string();
void lexer_putback();
char *lexer_get_string();
char* lexer_get_string_token();
int isVCNNN(char * value);
char* lexer_get_number();
char * lexer_get_id();
void lexer_token_putback(Token * token);
void init_tab_token();
char* lexer_get_comment_1();
char* lexer_get_comment_2();
Token* lexer_get_next_token();
Token * lexer_scan_file();
void skip_whitespace();

#endif