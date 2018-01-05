#ifndef ARITHMETIC_H
#define ARITHMETIC_H

extern long program_k;
int getIdNumIfExistsOrFreeMemoryAddressOtherwise(char* id);
int getFreeMemoryAddress();
/*
VAR a b[5] c d BEGIN a := b[c] + b[d]; END
*/

void convertStringToNumberAndPutInRegister(char* num){
  if(debug) printf("String to convert: %s\n", num);
  char *end;
  long lnum = strtol(num, &end, 10);
  if (num == end ) { // got identifier
    if(debug) printf("Got memory adress identifier, loading into register: '%s'\n", num);
    if (doesStringContainIdSeparator(num)) { // does id is of form a[b]
        char* bId = strrchr(num, '|') + 1;
        int index = (int)(bId - num - 1);
        int bAddr = getIdNumIfExists(bId);

        char* aId = malloc(sizeof(char)*index);
        memset(aId, '\0', index+1);
        strncpy(aId, num, index);
        char* a0Id = concat(aId, "0");
        int a0IdAddr = getIdNumIfExists(a0Id);

        int a0IdAddrLen = snprintf( NULL, 0, "%d", a0IdAddr );
        char* a0IdAddrString = malloc( a0IdAddrLen + 1 );
        snprintf( a0IdAddrString, a0IdAddrLen + 1, "%d", a0IdAddr );

        int tmpMemAddr = getFreeMemoryAddress();

        convertStringToNumberAndPutInRegister(a0IdAddrString); // put a0 adress in register
        printf("STORE %d\n", tmpMemAddr); program_k++;
        printf("LOAD %d\n", bAddr); program_k++;
        printf("ADD %d\n", tmpMemAddr); program_k++;
        printf("STORE %d\n", tmpMemAddr); program_k++;
        printf("LOADI %d\n", tmpMemAddr); program_k++;
        free(aId);
        free(a0Id);
        free(a0IdAddrString);
    } else {
      int i = getIdNumIfExists(num);
      printf("LOAD %d\n", i); program_k++;
    }
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
  int aIdNum = getIdNumIfExistsOrFreeMemoryAddressOtherwise(a);
  if (aIdNum > ids_count) {
    convertStringToNumberAndPutInRegister(a);
    printf("STORE %d\n", aIdNum); program_k++;
  } else {
    printf("LOAD %d\n", aIdNum); program_k++;
    aIdNum = getFreeMemoryAddress();
    printf("STORE %d\n", aIdNum); program_k++;
  }
  int bIdNum = getIdNumIfExistsOrFreeMemoryAddressOtherwise(b);
  if (bIdNum > ids_count) {
    convertStringToNumberAndPutInRegister(b);
    printf("STORE %d\n", bIdNum); program_k++;
  } else {
    printf("LOAD %d\n", bIdNum); program_k++;
    bIdNum = getFreeMemoryAddress();
    printf("STORE %d\n", bIdNum); program_k++;
  }
  char* result = strdup("0"); // neccessary, will be freed inside putValueToTmp
  putValueToTmp(result);
  int pointOfReturn = program_k;
  printf("LOAD %d\n", aIdNum); program_k++;
  printf("JZERO %ld\n", (program_k+13)); program_k++;
      printf("DEC\n"); program_k++;
      printf("JODD %ld\n", (program_k+4)); program_k++;
          printf("LOAD %d\n", ids_count); program_k++;
          printf("ADD %d\n", bIdNum); program_k++;
          printf("STORE %d\n", ids_count); program_k++;
      printf("LOAD %d\n", aIdNum); program_k++;
      printf("SHR\n"); program_k++;
      printf("STORE %d\n", aIdNum); program_k++;
      printf("LOAD %d\n", bIdNum); program_k++;
      printf("SHL\n"); program_k++;
      printf("STORE %d\n", bIdNum); program_k++;
  printf("JUMP %d\n", pointOfReturn); program_k++;
  free(a);
  free(b);
}

void divide(char* a, char* b) {
	if(debug) printf("divide: %s %s\n", a, b);
  if (strcmp(b, "0") == 0) {
    if(debug) printf("Dividing by zero.\n");
    printf("ZERO\nSTORE %d\n", ids_count);  program_k += 2;
  }

  int remainIdNum = getIdNumIfExistsOrFreeMemoryAddressOtherwise(a);
  if (remainIdNum > ids_count) {
    convertStringToNumberAndPutInRegister(a);
  } else {
    printf("LOAD %d\n", remainIdNum); program_k++;
    remainIdNum = getFreeMemoryAddress();
  }
  printf("STORE %d\n", remainIdNum); program_k++;

  int scaledDivisorIdNum = getIdNumIfExistsOrFreeMemoryAddressOtherwise(b);
  if (scaledDivisorIdNum > ids_count) {
    convertStringToNumberAndPutInRegister(b);
  } else {
    printf("LOAD %d\n", scaledDivisorIdNum); program_k++;
    scaledDivisorIdNum = getFreeMemoryAddress();
  }
  printf("STORE %d\n", scaledDivisorIdNum); program_k++;

  int resultIdNum = getFreeMemoryAddress(); // = 0
  convertStringToNumberAndPutInRegister("0");
  printf("STORE %d\n", resultIdNum); program_k++;
	int multipleIdNum = getFreeMemoryAddress(); // = 1
  convertStringToNumberAndPutInRegister("1");
  printf("STORE %d\n", multipleIdNum); program_k++;


  printf("LOAD %d\n", scaledDivisorIdNum); program_k++;
  printf("JZERO %ld\n", (program_k+52)); program_k++; // dzielenie przez zero

  int pointOfReturn = program_k;
  printf("LOAD %d\n", remainIdNum); program_k++;
  printf("SUB %d\n", scaledDivisorIdNum); program_k++;
  printf("JZERO %ld\n", program_k+8); program_k++; //while (scaledDivisor < remain=dividend)
      printf("LOAD %d\n", scaledDivisorIdNum); program_k++;
      printf("SHL\n"); program_k++;
      printf("STORE %d\n", scaledDivisorIdNum); program_k++;
      printf("LOAD %d\n", multipleIdNum); program_k++;
      printf("SHL\n"); program_k++;
      printf("STORE %d\n", multipleIdNum); program_k++;
      printf("JUMP %d\n", pointOfReturn); program_k++; // end while

  // powtórz raz pętlę, żeby zrobić do..while
  printf("LOAD %d\n", scaledDivisorIdNum); program_k++;
  printf("INC\n"); program_k++;
  printf("SUB %d\n", remainIdNum); program_k++;
  printf("JZERO %ld\n", program_k+4); program_k++; // do ifa
  printf("DEC\n"); program_k++;
  printf("JZERO %ld\n", program_k+2); program_k++; // do ifa
  printf("JUMP %ld\n", program_k+7); program_k++; // omijamy ifa
      // if (remain >= scaled_divisor)
      printf("LOAD %d\n", remainIdNum); program_k++;
      printf("SUB %d\n", scaledDivisorIdNum); program_k++;
      printf("STORE %d\n", remainIdNum); program_k++;
      printf("LOAD %d\n", resultIdNum); program_k++;
      printf("ADD %d\n", multipleIdNum); program_k++;
      printf("STORE %d\n", resultIdNum); program_k++;
  printf("LOAD %d\n", scaledDivisorIdNum); program_k++;
  printf("SHR\n"); program_k++;
  printf("STORE %d\n", scaledDivisorIdNum); program_k++;
  printf("LOAD %d\n", multipleIdNum); program_k++;
  printf("SHR\n"); program_k++;
  printf("STORE %d\n", multipleIdNum); program_k++;
  // while (multiple != 0)
  pointOfReturn = program_k;
  printf("LOAD %d\n", multipleIdNum); program_k++; // unnecessary?
  printf("JZERO %ld\n", program_k+21); program_k++; // while
      printf("LOAD %d\n", scaledDivisorIdNum); program_k++;
      printf("INC\n"); program_k++;
      printf("SUB %d\n", remainIdNum); program_k++;
      printf("JZERO %ld\n", program_k+4); program_k++; // do ifa
      printf("DEC\n"); program_k++;
      printf("JZERO %ld\n", program_k+2); program_k++; // do ifa
      printf("JUMP %ld\n", program_k+7); program_k++; // omijamy ifa
          // if (remain >= scaled_divisor)
          printf("LOAD %d\n", remainIdNum); program_k++;
          printf("SUB %d\n", scaledDivisorIdNum); program_k++;
          printf("STORE %d\n", remainIdNum); program_k++;
          printf("LOAD %d\n", resultIdNum); program_k++;
          printf("ADD %d\n", multipleIdNum); program_k++;
          printf("STORE %d\n", resultIdNum); program_k++;
      printf("LOAD %d\n", scaledDivisorIdNum); program_k++;
      printf("SHR\n"); program_k++;
      printf("STORE %d\n", scaledDivisorIdNum); program_k++;
      printf("LOAD %d\n", multipleIdNum); program_k++;
      printf("SHR\n"); program_k++;
      printf("STORE %d\n", multipleIdNum); program_k++;
      printf("JUMP %d\n", pointOfReturn); program_k++;

  printf("LOAD %d\n", resultIdNum); program_k++;
  printf("STORE %d\n", ids_count); program_k++;
  free(a);
  free(b);
}

void mod(char* a, char* b) {
	if(debug) printf("mod: %s %s\n", a, b);
  if (strcmp(b, "0") == 0) {
    if(debug) printf("Modulo zero.\n");
    printf("ZERO\nSTORE %d\n", ids_count);  program_k += 2;
  }

  int remainIdNum = getIdNumIfExistsOrFreeMemoryAddressOtherwise(a);
  if (remainIdNum > ids_count) {
    convertStringToNumberAndPutInRegister(a);
  } else {
    printf("LOAD %d\n", remainIdNum); program_k++;
    remainIdNum = getFreeMemoryAddress();
  }
  printf("STORE %d\n", remainIdNum); program_k++;

  int scaledDivisorIdNum = getIdNumIfExistsOrFreeMemoryAddressOtherwise(b);
  if (scaledDivisorIdNum > ids_count) {
    convertStringToNumberAndPutInRegister(b);
  } else {
    printf("LOAD %d\n", scaledDivisorIdNum); program_k++;
    scaledDivisorIdNum = getFreeMemoryAddress();
  }
  printf("STORE %d\n", scaledDivisorIdNum); program_k++;

  int resultIdNum = getFreeMemoryAddress(); // = 0
  convertStringToNumberAndPutInRegister("0");
  printf("STORE %d\n", resultIdNum); program_k++;
	int multipleIdNum = getFreeMemoryAddress(); // = 1
  convertStringToNumberAndPutInRegister("1");
  printf("STORE %d\n", multipleIdNum); program_k++;

  printf("LOAD %d\n", scaledDivisorIdNum); program_k++;
  printf("JZERO %ld\n", (program_k+52)); program_k++; // dzielenie przez zero

  int pointOfReturn = program_k;
  printf("LOAD %d\n", remainIdNum); program_k++;
  printf("SUB %d\n", scaledDivisorIdNum); program_k++;
  printf("JZERO %ld\n", program_k+8); program_k++; //while (scaledDivisor < remain=dividend)
      printf("LOAD %d\n", scaledDivisorIdNum); program_k++;
      printf("SHL\n"); program_k++;
      printf("STORE %d\n", scaledDivisorIdNum); program_k++;
      printf("LOAD %d\n", multipleIdNum); program_k++;
      printf("SHL\n"); program_k++;
      printf("STORE %d\n", multipleIdNum); program_k++;
      printf("JUMP %d\n", pointOfReturn); program_k++; // end while

  // powtórz raz pętlę, żeby zrobić do..while
  printf("LOAD %d\n", scaledDivisorIdNum); program_k++;
  printf("INC\n"); program_k++;
  printf("SUB %d\n", remainIdNum); program_k++;
  printf("JZERO %ld\n", program_k+4); program_k++; // do ifa
  printf("DEC\n"); program_k++;
  printf("JZERO %ld\n", program_k+2); program_k++; // do ifa
  printf("JUMP %ld\n", program_k+4); program_k++; // omijamy ifa
      // if (remain >= scaled_divisor)
      printf("LOAD %d\n", remainIdNum); program_k++;
      printf("SUB %d\n", scaledDivisorIdNum); program_k++;
      printf("STORE %d\n", remainIdNum); program_k++;
  printf("LOAD %d\n", scaledDivisorIdNum); program_k++;
  printf("SHR\n"); program_k++;
  printf("STORE %d\n", scaledDivisorIdNum); program_k++;
  printf("LOAD %d\n", multipleIdNum); program_k++;
  printf("SHR\n"); program_k++;
  printf("STORE %d\n", multipleIdNum); program_k++;
  // while (multiple != 0)
  pointOfReturn = program_k;
  printf("LOAD %d\n", multipleIdNum); program_k++; // unnecessary?
  printf("JZERO %ld\n", program_k+18); program_k++; // while
      printf("LOAD %d\n", scaledDivisorIdNum); program_k++;
      printf("INC\n"); program_k++;
      printf("SUB %d\n", remainIdNum); program_k++;
      printf("JZERO %ld\n", program_k+4); program_k++; // do ifa
      printf("DEC\n"); program_k++;
      printf("JZERO %ld\n", program_k+2); program_k++; // do ifa
      printf("JUMP %ld\n", program_k+4); program_k++; // omijamy ifa
          // if (remain >= scaled_divisor)
          printf("LOAD %d\n", remainIdNum); program_k++;
          printf("SUB %d\n", scaledDivisorIdNum); program_k++;
          printf("STORE %d\n", remainIdNum); program_k++;
      printf("LOAD %d\n", scaledDivisorIdNum); program_k++;
      printf("SHR\n"); program_k++;
      printf("STORE %d\n", scaledDivisorIdNum); program_k++;
      printf("LOAD %d\n", multipleIdNum); program_k++;
      printf("SHR\n"); program_k++;
      printf("STORE %d\n", multipleIdNum); program_k++;
      printf("JUMP %d\n", pointOfReturn); program_k++;

  printf("LOAD %d\n", remainIdNum); program_k++;
  printf("STORE %d\n", ids_count); program_k++;
  free(a);
  free(b);
}

#endif
