// File with aux functions

#ifndef __aux__
#define __aux__

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
