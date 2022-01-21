#include "../headers/parser.h"

char* erreurs[] = {
  // column directives
  "ERROR_PK", "ERROR_FK", "ERROR_CHECK", "ERROR_NN", "ERROR_BETWEEN",
  "ERROR_INDEX", "ERROR_DEFAULT", "ERROR_UNIQUE",
  // data types
  "ERROR_NUM", "ERROR_INT", "ERROR_D", "ERROR_TS",
  "ERROR_VC", "ERROR_VCNNN", "ERROR_CLOB", "ERROR_BLOB", "ERROR_JSON",
  // table directives
  "ERROR_TD_COLPREFIX", "ERROR_TD_SELECT",
  // comments
  "ERROR_DOUBLE_HYPHEN", "ERROR_OPN_BRCKT", "ERROR_CLS_BRCKT", "ERROR_COMMENT",
  // other
  "ERROR_ID", "ERROR_VIEW", "ERROR_NL", "ERROR_VALUE", "ERROR_COMMA",
  "ERROR_EOF", "ERROR_ERR", "ERROR_WHITESPACE", "ERROR_NUMBER", "ERROR_STRING"
};

void test_symbole(CODE_LEX code) {
  if (code != token->code) error((Error)token);
  else lexer_get_next_token();
}

void error(Error err) {
  printf("erreur de type :%s", erreurs[err]);
  exit(-1);
}

void program() {
  if (token->code == TOKEN_ID) {
    table();
    program();
  }
  if (token->code == TOKEN_VIEW) {
    view ();
    program();
  }
}

void view() {
  test_symbole(TOKEN_VIEW);
  test_symbole(TOKEN_ID);
  test_symbole(TOKEN_ID);
  while(token->code != '\n') {
    test_symbole(TOKEN_ID);
  }
}

void table() {
  test_symbole(TOKEN_ID);
  while (token->code == TOKEN_TD_COLPREFIX
        || token->code == TOKEN_TD_SELECT)
  {
    table_directives();
  }
  test_symbole(TOKEN_NL);
  column();
  while (token->code == TOKEN_WHITESPACE) {
    column();
  }
}

void table_directives() {
  switch (token->code) {
    case TOKEN_TD_COLPREFIX:
      colprefix_directive();
      break;
    case TOKEN_TD_SELECT:
      test_symbole(TOKEN_TD_SELECT);
      break;
  }
}

void column() {
  test_symbole(TOKEN_WHITESPACE);
  test_symbole(TOKEN_ID);
  type();
  constraint();
  test_symbole(TOKEN_NL);
}

void colprefix_directive() {
  lexer_get_next_token();
  if(token->code == TOKEN_ID) {
    lexer_get_next_token();
  }
}

void type() {
  for (CODE_LEX code = TOKEN_NUM; code <= TOKEN_JSON; code++) {
    if (token->code == code) {
      lexer_get_lexer_get_next_token();
      break;
    }
  }
}

void constraint() {
  switch (token->code) {
    case TOKEN_PK:
     test_symbole(TOKEN_PK);
     break;
    case TOKEN_FK:
     fk_constraint();
     break;
    case TOKEN_CHECK:
     check_constraint();
     break;
    case TOKEN_NN:
     test_symbole(TOKEN_NN);
     break;
    case TOKEN_BETWEEN:
     between_constraint();
     break;
    case TOKEN_INDEX:
     test_symbole(TOKEN_INDEX);
     break;
    case TOKEN_DEFAULT:
     default_constraint();
     break;
    case TOKEN_UNIQUE:
     test_symbole(TOKEN_UNIQUE);
     break;
  }
}

void fk_constraint() {
  test_symbole(TOKEN_FK);
  test_symbole(TOKEN_ID);
}

void check_constraint() {
  test_symbole(TOKEN_CHECK);
  test_symbole(TOKEN_VALUE);
  while(token->code == TOKEN_COMMA) {
    lexer_get_next_token();
    test_symbole(TOKEN_VALUE);
  }
} 

void between_consrtraint(){
  test_symbole(TOKEN_BETWEEN);
  switch (token->code)
  {
  case TOKEN_NUMBER:
    test_symbole(TOKEN_NUMBER);
    test_symbole(TOKEN_NUMBER);
    break;
  case TOKEN_STRING:
    test_symbole(TOKEN_STRING);
    test_symbole(TOKEN_STRING);
    break;
  default:
    error(TOKEN_VALUE);
    break;
  }
}