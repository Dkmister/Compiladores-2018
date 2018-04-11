#include "main.h"

extern FILE *yyin;
extern int yyparse(void);
extern int yylex(void);

int main(int argc, char **argv)
{

  int token = 0;

  if (argc>3){
    fprintf(stderr, "\n\nEntradas de mais recebidas. Deve ser provido pelo menos um arquivo de entrada, da seguinte forma - ./etapa3 entrada.txt -.");
    fprintf(stderr, "\nOpcionalmente pode ser provido também um arquivo de saída para decompilação, - ./etapa3 entrada.txt saida.txt -.\n\n\n");
    exit(1);
  }

  if (argc<2){
    fprintf(stderr, "\n\nDeve ser provido pelo menos um arquivo de entrada, da seguinte forma - ./etapa3 entrada.txt -.");
    fprintf(stderr, "\nOpcionalmente pode ser provido também um arquivo de saída para decompilação, - ./etapa3 entrada.txt saida.txt -.\n\n\n");
    exit(1);
  }

  if (argc<3){
    fprintf(stderr, "\n\nArquivo de entrada recebido, arquivo de saída não.");
    fprintf(stderr, "\nPara que seja salvo o resultado da decompilação é necessário um arquivo de saída - ./etapa3 entrada.txt saida.txt -.\n\n\n");
  } else {
    fprintf(stderr, "\n\nArquivos de entrada e saída recebidos.");
  }

  if((yyin = fopen(argv[1],"r")) == 0)
  {
    fprintf(stderr, "\n\nNao foi possível abrir o arquivo de entrada - %s -.\n\n\n",argv[1]);
    exit(2);
  }

  initMe();

  yyparse();
  
  /* HASH PRINT
  hashPrint(); */

  /* AST PRINT */
  ast_print();

  /* DECOMPILE */
  program_to_file(argv[2]);

  return 0;
}
