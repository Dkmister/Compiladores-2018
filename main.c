#include "main.h"
extern FILE *yyin;


int main(int argc, char **argv)
{

  int token = 0;

  if (argc<2){
    fprintf(stderr,"Chame pelamor de Deus : etapa1 nome_do_arquivo.\n ");
    exit(1);
  }

  if( (yyin = (fopen((argv[1]),"r") == 0) ) )
  {
    printf("Nao pode abrir o arquivo %s, caramba >:( ",argv[1]);
    exit(2);
  }

  initMe();

  /*while(isRunning())
  {

    token = yylex();
    printf("Linha numero: %d ;\r Token: %d ; \n", getLineNumber(), token);

  }*/

  return 0;
}
