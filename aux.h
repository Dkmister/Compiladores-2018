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

// Lex function declaration

int yylex();

/// Constants

#define LT_INT    1
#define LT_FLOAT  2
#define LT_CHAR   3
#define LT_STRING 4
#define LT_IDENT  5
