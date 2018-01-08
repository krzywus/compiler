#ifndef ERRORS_H
#define ERRORS_H

/* Bison */
#define SYNTAX_ERROR "syntax error"
#define SECOND_DECLARATION "Second identifier declaration."
#define UNDECLARED_VARIABLE "Undeclared variable."
#define ZERO_ARRAY_DECLARATION "Array declaration of size 0."
#define REALLOCATE_FAILURE "Failed to reallocate memory."
#define UNINITIALIZED_VARIABLE "Variable was not initialized before usage."
#define FOR_LOOP_ENDING_FAILURE "Failed to end FOR loop."
#define WHILE_LOOP_ENDING_FAILURE "Failed to end WHILE loop."
#define IF_ENDING_FAILURE "Failed to end IF statement."
#define LOOP_ENDING_FAILURE "Failed to end IF statement."


#define SYNTAX_ERROR_ERROR_CODE              2
#define SECOND_DECLARATION_ERROR_CODE        21
#define UNDECLARED_VARIABLE_ERROR_CODE       22
#define ZERO_ARRAY_DECLARATION_ERROR_CODE    25
#define REALLOCATE_FAILURE_ERROR_CODE        26
#define UNINITIALIZED_VARIABLE_ERROR_CODE    27
#define FOR_LOOP_ENDING_FAILURE_ERROR_CODE   28
#define WHILE_LOOP_ENDING_FAILURE_ERROR_CODE 29
#define IF_ENDING_FAILURE_ERROR_CODE         30
#define LOOP_ENDING_FAILURE_ERROR_CODE       31

#define DEFAULT_ERROR_CODE                 99


long getErrorCode(char const *s){
  if(strcmp(s, SYNTAX_ERROR) == 0){
    return SYNTAX_ERROR_ERROR_CODE;
  }
  if(strcmp(s, SECOND_DECLARATION) == 0){
    return SECOND_DECLARATION_ERROR_CODE;
  }
  if(strcmp(s, UNDECLARED_VARIABLE) == 0){
    return UNDECLARED_VARIABLE_ERROR_CODE;
  }
  if(strcmp(s, ZERO_ARRAY_DECLARATION) == 0){
    return ZERO_ARRAY_DECLARATION_ERROR_CODE;
  }
  if(strcmp(s, REALLOCATE_FAILURE) == 0){
    return REALLOCATE_FAILURE_ERROR_CODE;
  }
  if(strcmp(s, UNINITIALIZED_VARIABLE) == 0){
    return UNINITIALIZED_VARIABLE_ERROR_CODE;
  }
  if(strcmp(s, FOR_LOOP_ENDING_FAILURE) == 0){
    return FOR_LOOP_ENDING_FAILURE_ERROR_CODE;
  }
  if(strcmp(s, WHILE_LOOP_ENDING_FAILURE) == 0){
    return WHILE_LOOP_ENDING_FAILURE_ERROR_CODE;
  }
  if(strcmp(s, IF_ENDING_FAILURE) == 0){
    return IF_ENDING_FAILURE_ERROR_CODE;
  }
  if(strcmp(s, LOOP_ENDING_FAILURE) == 0){
    return LOOP_ENDING_FAILURE_ERROR_CODE;
  }
  return DEFAULT_ERROR_CODE;
}

#endif
