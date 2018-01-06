#ifndef COMMANDS_H
#define COMMANDS_H

extern long program_k;

void GET() {
	printf("GET\n");
	program_k++;
}

void PUT() {
	printf("PUT\n");
	program_k++;
}

void LOAD(int i) {
	printf("LOAD %d\n", i);
	program_k++;
}

void LOADI(int i) {
	printf("LOADI %d\n", i);
	program_k++;
}

void STORE(int i) {
	printf("STORE %d\n", i);
	program_k++;
}

void STOREI(int i) {
	printf("STOREI %d\n", i);
	program_k++;
}

void ADD(int i) {
	printf("ADD %d\n", i);
	program_k++;
}

void ADDI(int i) {
	printf("ADDI %d\n", i);
	program_k++;
}

void SUB(int i) {
	printf("SUB %d\n", i);
	program_k++;
}

void SUBI() {
	printf("SUBI\n");
	program_k++;
}

void SHR() {
	printf("SHR\n");
	program_k++;
}

void SHL() {
	printf("SHL\n");
	program_k++;
}

void INC() {
	printf("INC\n");
	program_k++;
}

void DEC() {
	printf("DEC\n");
	program_k++;
}

void ZERO() {
	printf("ZERO\n");
	program_k++;
}

void JUMP(int i) {
	printf("JUMP %d\n", i);
	program_k++;
}

void JZERO(int i) {
	printf("JZERO %d\n", i);
	program_k++;
}

void JODD(int i) {
	printf("JODD %d\n", i);
	program_k++;
}

void HALT() {
	printf("HALT\n");
	program_k++;
}

#endif
