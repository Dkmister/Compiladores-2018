#include "aux.h"
#include "hash.h"


void initMe(void) { hashInit(); runningVar = 1; }

int isRunning(void) { return runningVar; }

void foundEof(void) { runningVar = 0; }

int getLineNumber(void) { extern int yylineno; return yylineno; }

void yyerror(char const *mensagem) { fprintf(stderr, "%s in line %d\n", mensagem, getLineNumber()); exit(3); }

void semanticError(char const *mensagem) { fprintf(stderr, "Semantic Error in line %d: %s\n", getLineNumber(), mensagem); exit(4); }
