#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../headers/lex.h"

int Lines = 1;
int Columns = 0;


char *token_str[] = {
		"TOKEN_ID",
		"TOKEN_NL",
		"TOKEN_VIEW",
		"TOKEN_TD_SELECT",
		"TOKEN_TD_COLPREFIX",
		"TOKEN_NUM",
		"TOKEN_INT",
		"TOKEN_D",
		"TOKEN_TS",
		"TOKEN_TSTZ",
		"TOKEN_VC",
		"TOKEN_VCNNN",
		"TOKEN_CLOB",
		"TOKEN_BLOB",
		"TOKEN_JSON",
		"TOKEN_PK",
		"TOKEN_FK",
		"TOKEN_CHECK",
		"TOKEN_NN",
		"TOKEN_BETWEEN",
		"TOKEN_INDEX",
		"TOKEN_DEFAULT",
		"TOKEN_UNIQUE",
		// string between '' quotes
		"TOKEN_STRING",
		// litteral number: 344,4 ,56 hhhhh
		"TOKEN_NUMBER",
		"TOKEN_COMMENT",
		"TOKEN_COMMA",
		"TOKEN_EOF",
		"TOKEN_ERR",
		"TOKEN_WHITESPACE"

	};

void lexer_init()
{
	lexer = calloc(1, sizeof(Lexer));
}
void get_next_car()
{
	if (Putback)
	{
		lexer->c = Putback;
		Putback = 0;
		return;
	}
	if (lexer->c == '\n')
	{
		Lines++;
		Columns = 0;
	}

	lexer->c = fgetc(inputFile);
	Columns++;
}

Token *token_init(int type, char *value)
{
	Token *token = calloc(1, sizeof(Token));
	token->type = type;
	token->value = value;
	printf("< %s , %s > \n", token_str[token->type], token->value);
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

	while (lexer->c != ' ' && lexer->c != '\n' && lexer->c != '\b' && lexer->c != '\r' && lexer->c != '\f' && lexer->c != EOF)
	{
		char *s = lexer_get_caracter_as_string();
		value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
		strcat(value, s);
		get_next_car();
	}

	lexer_putback();
	return value;
}

char *lexer_get_string_token()
{
	get_next_car();

	char *value = calloc(1, sizeof(char));
	value[0] = '\0';
	while (strcmp(lexer_get_caracter_as_string(), "'") != 0 && lexer->c != EOF)
	{
		char *s = lexer_get_caracter_as_string();
		value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
		strcat(value, s);
		get_next_car();
	}
	if (lexer->c == EOF)
		lexer_putback();

	return value;
}

int isVCNNN(char *value)
{
	int isVCNNN = 0;
	if (value[0] == 'v' && value[1] == 'c')
	{
		int i = 2;
		while (isdigit(value[i]))
		{
			i++;
		}
		if (i == strlen(value))
			isVCNNN = 1;
	};
	return isVCNNN;
}

char *lexer_get_number()
{

	char *value = calloc(2, sizeof(char));
	int i = 0;
	while (isdigit(lexer->c) || lexer->c == '.')
	{
		i++;
		value = realloc(value, (strlen(value) + i) * sizeof(char));
		strcat(value, lexer_get_caracter_as_string());
		get_next_car();
	}
	lexer_putback();

	return value;
}
char *lexer_get_id()
{
	char *value = calloc(2, sizeof(char));
	int i = 0;
	value[0] = lexer->c;
	while (isalnum(lexer->c) || lexer->c == '_')
	{ // i++;
		get_next_car();
		char *str = lexer_get_caracter_as_string();
		value = realloc(value, (strlen(value) + strlen(str) + 1) * sizeof(char));
		if (isalnum(lexer->c) || lexer->c == '_')
			strcat(value, lexer_get_caracter_as_string());
	}
	lexer_putback();
	return value;
}

void lexer_token_putback(Token *token)
{
	Putback_token = calloc(1, sizeof(Token));
	Putback_token->type = token->type;
	Putback_token->value = token->value;
}

void init_tab_token()
{
	get_next_car();

	int i = 0;
	while (lexer->c == ' ')
	{
		i++;
		get_next_car();
	}
	lexer_putback();
	if (i > 0)
	{
		Token *token = calloc(1, sizeof(Token));
		token->type = TOKEN_WHITESPACE;
		char *str = calloc(1, 5 * sizeof(char));
		token->value = i2a(i, str, 10);
		lexer_token_putback(token);
	}
}

char *lexer_get_comment_1()
{
	get_next_car();
	char *comment = calloc(2, sizeof(char));
	comment[0] = lexer->c;
	while (lexer->c != '\n' && lexer->c != EOF)
	{
		get_next_car();
		char *str = lexer_get_caracter_as_string();
		comment = realloc(comment, sizeof(char) * (strlen(comment) + strlen(str) + 1));
		if (lexer->c != '\n' && lexer->c != EOF)
			strcat(comment, str);
	}
	lexer_putback();
	return comment;
}
char *lexer_get_comment_2()
{
	get_next_car();
	char *comment = calloc(2, sizeof(char));
	while (lexer->c != ']' && lexer->c != '[' && lexer->c != EOF)
	{
		char *str = lexer_get_caracter_as_string();
		comment = realloc(comment, sizeof(char) * (strlen(comment) + strlen(str) + 1));
		strcat(comment, str);
		get_next_car();
	}
	if (lexer->c == '[')
		return NULL;
	if (lexer->c == ']')
		return comment;
	if (lexer->c == EOF)
	{
		lexer_putback();
		return NULL;
	}
}
Token *lexer_get_next_token()
{
	char *car;
	if (Putback_token)
	{
		Token *token = token_init(Putback_token->type, Putback_token->value);
		Putback_token = NULL;
		return token;
	}
	if (Lines == 1 && Columns == 0)
	{
		get_next_car();
		int i = 0;
		while (lexer->c == ' ')
		{
			get_next_car();
			i++;
		}
		lexer_putback();
		char *str = calloc(1, 5 * sizeof(char));
		if (i > 0)
			return token_init(TOKEN_WHITESPACE, i2a(i, str, 10));
	}
	skip_whitespace();
	switch (lexer->c)
	{
	case ',':
		return token_init(TOKEN_COMMA, lexer_get_caracter_as_string());
		break;
	case '\n':
		car = lexer_get_caracter_as_string();
		init_tab_token();
		return token_init(TOKEN_NL, car);
		break;

	case ' ':
		return token_init(TOKEN_WHITESPACE, lexer_get_caracter_as_string());
		break;

	case EOF:
		return token_init(TOKEN_EOF, "EOF");
		break;
	default:
	{
		if (lexer->c == '-')
		{
			char *value = calloc(2, sizeof(char));
			value[0] = lexer->c;
			get_next_car();
			if (lexer->c == '-')
			{
				char *com = lexer_get_comment_1();
				return token_init(TOKEN_COMMENT, com);
			}
			free(value);
			lexer_putback();
		}
		if (lexer->c == '[')
		{
			char *comment = lexer_get_comment_2();
			if (comment != NULL)
			{
				return token_init(TOKEN_COMMENT, comment);
			}

			else
			{
				printf("ERROR: Invalid Token\n");
				exit(1);
			}
		}
		if (lexer->c == '/')
		{ // table directives
			char *directive = lexer_get_string();
			char *slash = calloc(1, (strlen(directive) + strlen("/") + 1) * sizeof(char));
			slash[0] = '/';
			strcat(slash, directive);
			if (strcmp(directive, "select") == 0)
				return token_init(TOKEN_TD_SELECT, slash);
			else if (strcmp(directive, "colprefix") == 0)
				return token_init(TOKEN_TD_COLPREFIX, slash);
			else if (strcmp(directive, "fk") == 0)
				return token_init(TOKEN_FK, slash);
			else if (strcmp(directive, "check") == 0)
				return token_init(TOKEN_CHECK, slash);
			else if (strcmp(directive, "nn") == 0)
				return token_init(TOKEN_NN, slash);
			else if (strcmp(directive, "unique") == 0)
				return token_init(TOKEN_UNIQUE, slash);
			else if (strcmp(directive, "default") == 0)
				return token_init(TOKEN_DEFAULT, slash);
			else if (strcmp(directive, "between") == 0)
				return token_init(TOKEN_BETWEEN, slash);
			else if (strcmp(directive, "index") == 0)
				return token_init(TOKEN_INDEX, slash);
			else if (strcmp(directive, "pk") == 0)
				return token_init(TOKEN_PK, slash);
			else
			{
				printf("ERROR: Invalid Token\n");
				exit(1);
			}
		}

		else
		{
			if (isdigit(lexer->c))
			{

				char *number = lexer_get_number();

				return token_init(TOKEN_NUMBER, number);
			}

			if (isalpha(lexer->c))
			{

				char *value = lexer_get_id();
				if (strcmp(value, "int") == 0)
					return token_init(TOKEN_INT, value);
				if (strcmp(value, "number") == 0)
					return token_init(TOKEN_NUMBER, value);
				if (strcmp(value, "d") == 0)
					return token_init(TOKEN_D, value);
				if (strcmp(value, "clob") == 0)
					return token_init(TOKEN_CLOB, value);
				if (strcmp(value, "blob") == 0)
					return token_init(TOKEN_BLOB, value);
				if (strcmp(value, "json") == 0)
					return token_init(TOKEN_JSON, value);
				if (strcmp(value, "vc") == 0)
					return token_init(TOKEN_VC, value);
				if (strcmp(value, "ts") == 0)
					return token_init(TOKEN_TS, value);
				if (strcmp(value, "tstz") == 0)
					return token_init(TOKEN_TSTZ, value);
				if (isVCNNN(value))
					return token_init(TOKEN_VCNNN, value);
				if (strcmp(value, "view") == 0)
					return token_init(TOKEN_VIEW, value);
				return token_init(TOKEN_ID, value);
			}

			if (strcmp(lexer_get_caracter_as_string(), "'") == 0)
			{
				char *string = lexer_get_string_token();
				if (Putback == EOF)
				{
					printf("ERROR: Invalid Token\n");
					exit(1);
				}
				return token_init(TOKEN_STRING, string);
			}
		}
		printf("ERROR: Invalid Token\n");
		exit(1);
	}
	}
}
void skip_whitespace()
{

	get_next_car();
	while (lexer->c == '\b' || lexer->c == '\r' || lexer->c == '\f' || lexer->c == ' ')
	{
		get_next_car();
	}
}
// int main(int argc, char *argv[])
// {
// 	if (argc != 2)
// 	{
// 		printf("Please insert all requierements to compile the program");
// 		exit(1);
// 	}
// 	if ((inputFile = fopen(argv[1], "r")) == NULL)
// 	{
// 		printf("Could not open the folder");
// 		exit(1);
// 	}
// 	lexer_init();
// 	lexer_get_next_token();

// 	return 0;
// }