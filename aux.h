#include <stdio.h>
#include <stdlib.h>

/// Variables

// Execution control var
int runningVar;

/// Functions

// Initialization funcion
void initMe(void);

// Returns true for running and false for finished
int isRunning(void);

// Used by lex to tell that he has found EOF
void foundEof(void);

// Returns line number of Lex
int getLineNumber(void);

// YYPARSE ERROR, retorna mensagem de erro e exit(3)
void yyerror (char const *mensagem);

void semanticError(char const *mensagem);

// Lex function declaration

int yylex();

