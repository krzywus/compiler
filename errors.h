
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
#define SYNTAX_ERROR_ERROR_CODE         2
#define SECOND_DECLARATION_ERROR_CODE   21

#define DEFAULT_ERROR_CODE              99


int getErrorCode(char const *s){
  if(strcmp(s, SYNTAX_ERROR) == 0){
    return SYNTAX_ERROR_ERROR_CODE;
  }
  if(strcmp(s, SECOND_DECLARATION) == 0){
    return SECOND_DECLARATION_ERROR_CODE;
  }
  return DEFAULT_ERROR_CODE;
}
