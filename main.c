#include "main.h"
extern FILE *yyin;


int main(int argc, char **argv)
{

  int token = 0;
  
  initMe();

  if (argc == 1)
    yyin = fopen(argv[1], "r");
  else
    yyin = stdin;

  while(isRunning())
  {

    token = yylex();
    printf("Line number: %d ;", getLineNumber());

  }
  return 0;
}
