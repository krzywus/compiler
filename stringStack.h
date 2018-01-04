#ifndef STRING_STACK_H
#define STRING_STACK_H

#define MAXSIZE 1000

extern void yyerror(char const *);

struct stack {
  char** stk;
  int top;
};
typedef struct stack STACK;

void initStack(STACK *s) {
    s->stk = malloc(sizeof(char*)*MAXSIZE);
}

void finalizeStack(STACK *s) {
    free(s->stk);
    free(s);
}

void push (STACK *s, char* instruction) {
    if (s->top == (MAXSIZE - 1)) {
        yyerror(STACK_OVERFLOW);
        return;
    }
    else {
        s->top = s->top + 1;
        s->stk[s->top] = instruction;
    }
}

char* pop (STACK *s) {
    char* instruction;
    if (s->top <= - 1) {
        yyerror(EMPTY_STACK);
        return NULL;
    }
    else {
        instruction = s->stk[s->top];
        s->top = s->top - 1;
    }
    return(instruction);
}

int isEmpty(STACK *s){
    return s->top == 0 ? 1 : 0;
}


#endif