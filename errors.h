#ifndef ERRORS_H
#define ERRORS_H

/* Flex */
#define VAR_STATE_ERROR "Second VAR section."
#define BEGINZ_STATE_ERROR "Missing VAR section or second BEGIN section."
#define END_STATE_ERROR "Program was not started or already finished."
#define ILLEGAL_IDENTIFIER "Illegal identifier."
#define VAR_STATE_ERROR_CODE            11
#define BEGINZ_STATE_ERROR_CODE         12
#define END_STATE_ERROR_CODE            13
#define ILLEGAL_IDENTIFIER_ERROR_CODE   14

/* Bison */
#define SYNTAX_ERROR "syntax error"
#define SECOND_DECLARATION "Second identifier declaration."
#define UNDECLARED_VARIABLE "Undeclared variable."
#define EMPTY_STACK "Stack is Empty."
#define STACK_OVERFLOW "Stack is Full."
#define ZERO_ARRAY_DECLARATION "Array declaration of size 0."
#define SYNTAX_ERROR_ERROR_CODE            2
#define SECOND_DECLARATION_ERROR_CODE      21
#define UNDECLARED_VARIABLE_ERROR_CODE     22
#define EMPTY_STACK_ERROR_CODE             23
#define STACK_OVERFLOW_ERROR_CODE          24
#define ZERO_ARRAY_DECLARATION_ERROR_CODE  25

#define DEFAULT_ERROR_CODE                 99


int getErrorCode(char const *s){
  if(strcmp(s, SYNTAX_ERROR) == 0){
    return SYNTAX_ERROR_ERROR_CODE;
  }
  if(strcmp(s, SECOND_DECLARATION) == 0){
    return SECOND_DECLARATION_ERROR_CODE;
  }
  if(strcmp(s, UNDECLARED_VARIABLE) == 0){
    return UNDECLARED_VARIABLE_ERROR_CODE;
  }
  if(strcmp(s, EMPTY_STACK) == 0){
    return EMPTY_STACK_ERROR_CODE;
  }
  if(strcmp(s, STACK_OVERFLOW) == 0){
    return STACK_OVERFLOW_ERROR_CODE;
  }
  if(strcmp(s, ZERO_ARRAY_DECLARATION) == 0){
    return ZERO_ARRAY_DECLARATION_ERROR_CODE;
  }
  return DEFAULT_ERROR_CODE;
}

#endif
