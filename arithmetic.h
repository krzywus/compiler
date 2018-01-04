#ifndef ARITHMETIC_H
#define ARITHMETIC_H

extern long program_k;

void convertStringToNumberAndPutInRegister(char* num){
  if(debug) printf("String to convert: %s\n", num);
  char *end;
  long lnum = strtol(num, &end, 10);
  if (num == end ) { // got identifier
    if(debug) printf("Got memory adress identifier, loading into register.\n");
    int i = getIdNumIfExists(num);
    printf("LOAD %d\n", i); program_k++;
  } else {
    /** Trzeba wyliczyć otrzymaną liczbę poprzez instrukcje: "ZERO -> INC -> INC/SHL". */
    if(debug) printf("Got number, calculating and putting into register.\n");
    printCommandsForCreatingNumber(lnum);
  }
}

void putValueToTmp(char* num){
  if(debug) printf("putting number to tmp: %s\n", num);
  convertStringToNumberAndPutInRegister(num);
  printf("STORE %d\n", ids_count); program_k++;
  free(num);
}

void addition(char* a, char* b) {
	if(debug) printf("addition: %s %s\n", a, b);
  convertStringToNumberAndPutInRegister(a);
  printf("STORE %d\n", ids_count); program_k++;
  convertStringToNumberAndPutInRegister(b);
  printf("ADD %d\n", ids_count); program_k++;
  printf("STORE %d\n", ids_count); program_k++;
  free(a);
  free(b);
}

void substraction(char* a, char* b) {
	if(debug) printf("substraction: %s %s\n", a, b);
  convertStringToNumberAndPutInRegister(b);
  printf("STORE %d\n", ids_count); program_k++;
  convertStringToNumberAndPutInRegister(a);
  printf("SUB %d\n", ids_count); program_k++;
  printf("STORE %d\n", ids_count); program_k++;
  free(a);
  free(b);
}

void multiply(char* a, char* b) {
  if(debug) printf("multiply: %s %s\n", a, b);
  free(a);
  free(b);
}

void divide(char* a, char* b) {
	if(debug) printf("divide: %s %s\n", a, b);
  if (strcmp(b, "0") == 0) {
    if(debug) printf("Dividing by zero.\n");
    printf("ZERO\nSTORE %d\n", ids_count);  program_k += 2;
  }
  free(a);
  free(b);
}


void mod(char* a, char* b) {
	printf("mod: %s %s\n", a, b);
  free(a);
  free(b);
}

#endif
