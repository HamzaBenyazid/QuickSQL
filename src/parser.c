#include "../headers/parser.h"
#include "../headers/utils.h"

char* erreurs[] = {
  // column directives
  "ERROR_PK", "ERROR_FK", "ERROR_CHECK", "ERROR_NN", "ERROR_BETWEEN",
  "ERROR_INDEX", "ERROR_DEFAULT", "ERROR_UNIQUE",
  // data types
  "ERROR_NUM", "ERROR_INT", "ERROR_D", "ERROR_TS",
  "ERROR_VC", "ERROR_VCNNN", "ERROR_CLOB", "ERROR_BLOB", "ERROR_JSON",
  // table directives
  "ERROR_TD_COLPREFIX", "ERROR_TD_SELECT",
  // other
  "ERROR_ID", "ERROR_VIEW", "ERROR_NL", "ERROR_VALUE", "ERROR_COMMA",
  "ERROR_EOF", "ERROR_ERR", "ERROR_WHITESPACE", "ERROR_NUMBER", "ERROR_STRING"
};

int nbrWhiteSpaces;
void parse(){
  initTablesAndViewsAndIndexes();
  token=lexer_get_next_token();
  program();
}
void test_symbole(Type type) {
  if (token->type == TOKEN_COMMENT) comment();
  if (type != token->type) error(type,token->type);
  else token=lexer_get_next_token();
}

void error(Type expectedToken,Type foundToken) {
  printf("\nSyntax error in line %d: expected %s found %s\n",Lines,token_str[expectedToken],token_str[foundToken]);
  exit(-1);
}

void program() {
  while(token->type==TOKEN_NL || token->type==TOKEN_COMMENT) token=lexer_get_next_token();
  if (token->type == TOKEN_ID) {
    table();
    program();
  }
  if (token->type == TOKEN_VIEW) {
    view ();
    program();
  }
}

void view() {
  test_symbole(TOKEN_VIEW);
  addViewName(token->value);
  test_symbole(TOKEN_ID);
  addViewTableName(token->value);
  test_symbole(TOKEN_ID);
  while(token->type != TOKEN_NL && token->type !=TOKEN_EOF) {
    addViewTableName(token->value);
    test_symbole(TOKEN_ID);
  }
}

void table() {
  nbrWhiteSpaces = -1;
  addTableName(token->value);
  test_symbole(TOKEN_ID);
  while (token->type == TOKEN_TD_COLPREFIX
        || token->type == TOKEN_TD_SELECT)
  {
    table_directives();
  }
  test_symbole(TOKEN_NL);
  column();
  while (token->type == TOKEN_WHITESPACE) {
    column();
  }
}

void table_directives() {
  switch (token->type) {
    case TOKEN_TD_COLPREFIX:
      addTableDirective(token->type);
      colprefix_directive();
      break;
    case TOKEN_TD_SELECT:
      addTableDirective(token->type);
      test_symbole(TOKEN_TD_SELECT);
      break;
  }
}

void column() {
  if ((a2i(token->value) != nbrWhiteSpaces) && (nbrWhiteSpaces != -1)){
    printf("\nIndentationError in line %d: unexpected indent \n",Lines);
    exit(-1);
  }
  nbrWhiteSpaces = a2i(token->value);
  test_symbole(TOKEN_WHITESPACE);
  addColumnName(token->value);
  test_symbole(TOKEN_ID);
  type();
  constraint();
  test_symbole(TOKEN_NL);
}

void colprefix_directive() {
  token=lexer_get_next_token();
  addTableDirectiveArgument(token->value);
  if(token->type == TOKEN_ID) {
    token=lexer_get_next_token();
  }
}

void type() {
  for (Type type = TOKEN_NUM; type <= TOKEN_JSON; type++) {
    if (token->type == type) {
      addColumnType(type);
      if (type == TOKEN_VCNNN) addVCLength(token->value);
      token=lexer_get_next_token();
      break;
    }
  }
}

void constraint() {
  if(token->type==TOKEN_COMMENT){
    comment();
    return constraint();
  }
  switch (token->type) {
    case TOKEN_PK:
     addColumnDirective(token->type);
     test_symbole(TOKEN_PK);
     break;
    case TOKEN_FK:
     addColumnDirective(token->type);
     fk_constraint();
     break;
    case TOKEN_CHECK:
     addColumnDirective(token->type);
     check_constraint();
     break;
    case TOKEN_NN:
     addColumnDirective(token->type);
     test_symbole(TOKEN_NN);
     break;
    case TOKEN_BETWEEN:
     addColumnDirective(token->type);
     between_constraint();
     break;
    case TOKEN_INDEX:
     addColumnDirective(token->type);
     test_symbole(TOKEN_INDEX);
     break;
    case TOKEN_DEFAULT:
     addColumnDirective(token->type);
     default_constraint();
     break;
    case TOKEN_UNIQUE:
     addColumnDirective(token->type);
     test_symbole(TOKEN_UNIQUE);
     break;
    default :
      return;
  }
  constraint();

}

void fk_constraint() {
  test_symbole(TOKEN_FK);
  addColumnDirectiveArgument(token->value);
  test_symbole(TOKEN_ID);
}

void check_constraint() {
  test_symbole(TOKEN_CHECK);
  addColumnDirectiveArgument(token->value);
  if(token->type==TOKEN_STRING){
    test_symbole(TOKEN_STRING);
    while(token->type == TOKEN_COMMA) {
      token=lexer_get_next_token();
      addColumnDirectiveArgument(token->value);
      test_symbole(TOKEN_STRING);
    }
  }else{
    test_symbole(TOKEN_NUMBER);
    while(token->type == TOKEN_COMMA) {
      token=lexer_get_next_token();
      addColumnDirectiveArgument(token->value);
      test_symbole(TOKEN_NUMBER);
    }
  }
  
}

void between_constraint(){
  test_symbole(TOKEN_BETWEEN);
  switch (token->type)
  {
  case TOKEN_NUMBER:{
    addColumnDirectiveArgument(token->value);
    test_symbole(TOKEN_NUMBER);
    addColumnDirectiveArgument(token->value);
    test_symbole(TOKEN_NUMBER);
    }
    break;
  case TOKEN_STRING:{
    addColumnDirectiveArgument(token->value);
    test_symbole(TOKEN_STRING);
    addColumnDirectiveArgument(token->value);
    test_symbole(TOKEN_STRING);
    }
    break;
  // default:
  //   error(TOKEN_VALUE);
  //   break;
  }
}

void default_constraint() {
  test_symbole(TOKEN_DEFAULT);
  addColumnDirectiveArgument(token->value);
  if(token->type==TOKEN_NUMBER)
    test_symbole(TOKEN_NUMBER);
  else
    test_symbole(TOKEN_STRING);
    
}
void comment() {
  addComment(token->value);
  token=lexer_get_next_token();
}