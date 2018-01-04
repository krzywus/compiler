#ifndef ARITHMETIC_H
#define ARITHMETIC_H

void putValueToTmp(char* num){
  if(debug) printf("putting number to tmp: %s\n", num);
  char *end;
  long lnum = strtol(num, &end, 10);
  if (num == end ) { // got identifier
    int i = getIdNumIfExists(end);
    printf("LOAD %d\n", i);
  } else {
    printCommandsForCreatingNumber(lnum);
  }
  printf("STORE %d\n", ids_count);
  free(num);
}

void addition(char* a, char* b) {
	printf("addition: %s %s\n", a, b);
  char *end;
  long lnumA = strtol(a, &end, 10);
  if (end == a) {    // got identifier
    if(debug) printf("BISON DEBUG: got identifier, not value: %s\n", a);
    int i = getIdNumIfExists(a);
    printf("LOAD %d\n", i);
  } else {
    /** Trzeba wyliczyć otrzymaną liczbę poprzez instrukcje: "ZERO -> INC -> INC/SHL". */
    printCommandsForCreatingNumber(lnumA);
  }
  printf("STORE %d\n", ids_count);
  long lnumB = strtol(b, &end, 10);
  if (end == b) {    // got identifier
    if(debug) printf("BISON DEBUG: got identifier, not value: %s\n", b);;
    int i = getIdNumIfExists(b);
    printf("LOAD %d\n", i);
  } else {
    /** Trzeba wyliczyć otrzymaną liczbę poprzez instrukcje: "ZERO -> INC -> INC/SHL". */
    printCommandsForCreatingNumber(lnumB);
  }
  printf("ADD  %d\n", ids_count);
  free(a);
  free(b);
}

void substraction(char* a, char* b) {
	printf("substraction: %s %s\n", a, b);
  free(a);
  free(b);
}

void divide(char* a, char* b) {
	printf("divide: %s %s\n", a, b);
  free(a);
  free(b);
}

void multiply(char* a, char* b) {
	printf("multiply: %s %s\n", a, b);
  free(a);
  free(b);
}

void mod(char* a, char* b) {
	printf("mod: %s %s\n", a, b);
  free(a);
  free(b);
}

#endif