#include "aux.h"
#include "hash.h"


void initMe(void) { hashInit(); runningVar = 1; }

int isRunning(void) { return runningVar; }

void foundEof(void) { runningVar = 0; }

int getLineNumber(void) { extern int yylineno; return yylineno; }
