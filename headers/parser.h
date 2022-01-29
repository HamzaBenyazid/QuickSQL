#if !defined(PARSER)
#define PARSER

#include "lex.h"

// tableau des erreurs:
extern char* erreurs[];

void test_symbole(Type type);
void error(Type expectedToken,Type foundToken);
void parse();
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
void comment();


#endif // PARSER
