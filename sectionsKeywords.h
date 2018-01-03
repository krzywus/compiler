
void printLex(char* s);
void lexError(char* s);

long varFound(){
	printLex("found var");
	if(current_state != -1){
		lexError(VAR_STATE_ERROR);
		exit(VAR_STATE_ERROR_CODE);
	}
	current_state = VAR_STATE;
	return VAR;
}

long beginFound(){
	printLex("found begin");
	if(current_state != VAR_STATE){
		lexError(BEGINZ_STATE_ERROR);
		exit(BEGINZ_STATE_ERROR_CODE);
	}
	current_state = BEGINZ_STATE;
	return BEGINZ;
}

long endFound(){
	printLex("found end");
	if(current_state != BEGINZ_STATE){
		lexError(END_STATE_ERROR);
		exit(END_STATE_ERROR_CODE);
	}
	current_state = END_STATE;
	return END;
}
