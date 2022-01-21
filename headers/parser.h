#if !defined(PARSER)
#define PARSER

typedef enum {
    // column directives
    TOKEN_PK, TOKEN_FK, TOKEN_CHECK, TOKEN_NN, TOKEN_BETWEEN,
    TOKEN_INDEX, TOKEN_DEFAULT, TOKEN_UNIQUE,
    // data types
    TOKEN_NUM, TOKEN_INT, TOKEN_D, TOKEN_TS,
    TOKEN_VC, TOKEN_VCNNN, TOKEN_CLOB, TOKEN_BLOB, TOKEN_JSON,
    // table directives
    TOKEN_TD_COLPREFIX, TOKEN_TD_SELECT,
    // comments
    TOKEN_DOUBLE_HYPHEN, TOKEN_OPN_BRCKT, TOKEN_CLS_BRCKT, TOKEN_COMMENT,
    // other
    TOKEN_ID, TOKEN_VIEW, TOKEN_NL, TOKEN_VALUE, TOKEN_COMMA,
    TOKEN_EOF, TOKEN_ERR, TOKEN_WHITESPACE, TOKEN_NUMBER, TOKEN_STRING
} Token;

typedef enum {
    // column directives
    ERROR_PK, ERROR_FK, ERROR_CHECK, ERROR_NN, ERROR_BETWEEN,
    ERROR_INDEX, ERROR_DEFAULT, ERROR_UNIQUE,
    // data types
    ERROR_NUM, ERROR_INT, ERROR_D, ERROR_TS,
    ERROR_VC, ERROR_VCNNN, ERROR_CLOB, ERROR_BLOB, ERROR_JSON,
    // table directives
    ERROR_TD_COLPREFIX, ERROR_TD_SELECT,
    // comments
    ERROR_DOUBLE_HYPHEN, ERROR_OPN_BRCKT, ERROR_CLS_BRCKT, ERROR_COMMENT,
    // other
    ERROR_ID, ERROR_VIEW, ERROR_NL, ERROR_VALUE, ERROR_COMMA,
    ERROR_EOF, ERROR_ERR, ERROR_WHITESPACE, ERROR_NUMBER, ERROR_STRING
} Error;



// tableau des erreurs:
extern char* erreurs[];

Token current_token;
void next_token();

void test_symbole(Token code);
void error(Error erreur);

void program();
void view();
void table();
void table_directives();
void column();
void colprefix_directive();
void type();
void constraint();
void fk_constraint();
void check_constraint();
void between_constraint();
void default_constraint();
void commanet();



#endif // PARSER
