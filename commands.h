#ifndef COMMANDS_H
#define COMMANDS_H

using namespace std;

extern vector<string> commands;
extern long program_k;
extern long loadedMemory;

void GET() {
  stringstream ss;
  ss << "GET" << endl;
	commands.push_back(ss.str());
	program_k++;
}

void PUT() {
  stringstream ss;
  ss << "PUT" << endl;
	commands.push_back(ss.str());
	program_k++;
}

void LOAD(long i) {
  loadedMemory = i;
  stringstream ss;
  ss << "LOAD " << i << endl;
  commands.push_back(ss.str());
  program_k++;
}

void LOADI(long i) {
  stringstream ss;
  ss << "LOADI " << i << endl;
	commands.push_back(ss.str());
	program_k++;
}

void STORE(long i) {
  stringstream ss;
  ss << "STORE " << i << endl;
	commands.push_back(ss.str());
	program_k++;
}

void STOREI(long i) {
  stringstream ss;
  ss << "STOREI " << i << endl;
	commands.push_back(ss.str());
	program_k++;
}

void ADD(long i) {
  stringstream ss;
  ss << "ADD " << i << endl;
	commands.push_back(ss.str());
	program_k++;
}

void ADDI(long i) {
  stringstream ss;
  ss << "ADDI " << i << endl;
	commands.push_back(ss.str());
	program_k++;
}

void SUB(long i) {
  stringstream ss;
  ss << "SUB " << i << endl;
	commands.push_back(ss.str());
	program_k++;
}

void SUBI(long i) {
  stringstream ss;
  ss << "SUBI " << i << endl;
	commands.push_back(ss.str());
	program_k++;
}

void SHR() {
  stringstream ss;
  ss << "SHR" << endl;
	commands.push_back(ss.str());
	program_k++;
}

void SHL() {
  stringstream ss;
  ss << "SHL" << endl;
	commands.push_back(ss.str());
	program_k++;
}

void INC() {
  stringstream ss;
  ss << "INC" << endl;
	commands.push_back(ss.str());
	program_k++;
}

void DEC() {
  stringstream ss;
  ss << "DEC" << endl;
	commands.push_back(ss.str());
	program_k++;
}

void ZERO() {
  stringstream ss;
  ss << "ZERO" << endl;
	commands.push_back(ss.str());
	program_k++;
}

void JUMP(long i) {
  stringstream ss;
  ss << "JUMP " << i << endl;
	commands.push_back(ss.str());
	program_k++;
}

void JZERO(long i) {
  stringstream ss;
  ss << "JZERO " << i << endl;
	commands.push_back(ss.str());
	program_k++;
}

void JODD(long i) {
  stringstream ss;
  ss << "JODD " << i << endl;
	commands.push_back(ss.str());
	program_k++;
}

void HALT() {
  stringstream ss;
  ss << "HALT" << endl;
	commands.push_back(ss.str());
	program_k++;
}

#endif
