#include "main.h"

extern FILE *yyin;
extern int yyparse(void);
extern int yylex(void);

int main(int argc, char **argv)
{

  int token = 0;

  if (argc<2){
    fprintf(stderr,"Chame pelamor de Deus : etapa1 nome_do_arquivo.\n ");
    exit(1);
  }

  if((yyin = fopen(argv[1],"r")) == 0)
  {
    printf("Nao pode abrir o arquivo %s, caramba >:( ",argv[1]);
    exit(2);
  }

  initMe();

  yyparse();

  return 0;
}
