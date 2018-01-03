
#define SYNTAX_ERROR "syntax error"
#define SECOND_DECLARATION "Second identifier declaration."


int getErrorCode(char const *s){
  if(strcmp(s, SYNTAX_ERROR) == 0){
    return 2;
  }
  if(strcmp(s, SECOND_DECLARATION) == 0){
    return 21;
  }
  return 99;
}
