#ifndef COMMANDS_H
#define COMMANDS_H

void GET() {
	printf("GET\n");
}

void PUT() {
	printf("PUT\n");
}

void LOAD(int i) {
	printf("LOAD %d\n", i);
}

void LOADI(int i) {
	printf("LOADI %d\n", i);
}

void STORE(int i) {
	printf("STORE %d\n", i);
}

void STOREI(int i) {
	printf("STOREI %d\n", i);
}

void ADD(int i) {
	printf("ADD %d\n", i);
}

void ADDI(int i) {
	printf("ADDI %d\n", i);
}

void SUB(int i) {
	printf("SUB %d\n", i);
}

void SUBI() {
	printf("SUBI\n");
}

void SHR() {
	printf("SHR\n");
}

void SHL() {
	printf("SHL\n");
}

void INC() {
	printf("INC\n");
}

void DEC() {
	printf("DEC\n");
}

void ZERO() {
	printf("ZERO\n");
}

void JUMP(int i) {
	printf("JUMP %d\n", i);
}

void JZERO(int i) {
	printf("JZERO %d\n", i);
}

void JODD(int i) {
	printf("JODD %d\n", i);
}

void HALT() {
	printf("HALT\n");
}

#endif
