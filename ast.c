#include "ast.h"	

AST* new_ast(int type)
{
  AST* node = malloc(sizeof(AST));
  node->type = type;
  node->hash_pointer = NULL;
  node->son1 = NULL;
  node->son2 = NULL;
  node->son3 = NULL;
  node->son4 = NULL;
}

void ast_print()
{
  printf("\n| IMPRESSAO A PARTIR DA RAIZ DA AST |\n\n");
  node_print(main_node, 0);
}

void node_print(AST* printme, int level)
{
  if (printme == NULL)
    return;

  for(int i = 0; i < level; i++)
    printf("  ");

  printf("\n| ");
  print_name(printme->type);
  node_print(printme->son1, level+1);
  node_print(printme->son1, level+1);
  node_print(printme->son1, level+1);
  node_print(printme->son1, level+1);
}

void print_name(int type)
{
  switch (type) {

  case T_PROGRAMA:
    printf("PROGRAMA");
    break;

  case T_GLOBALS:
    printf("VARIAVEL GLOBAL");
    break;

  case T_GLOBALP:
    printf("PONTEIRO GLOBAL");
    break;

  case T_GLOBALV:
    printf("VETOR GLOBAL");
    break;

  case T_FUNCAO_D:
    printf("DECLARACAO FUNCAO");
    break;

  case T_FUNCAO_C:
    printf("CHAMADA FUNCAO");
    break;

  case T_BLOCO:
    printf("BLOCO");
    break;

  case T_ATRIBUICAO:
    printf("ATRIBUICAO");
    break;

  case T_IF:
    printf("IF");
    break;

  case T_IFELSE:
    printf("IFELSE");
    break;

  case T_WHILE:
    printf("WHILE");
    break;

  case T_FOR:
    printf("FOR");
    break;

  case T_READ:
    printf("READ");
    break;

  case T_PRINT:
    printf("PRINT");
    break;

  case T_RETURN:
    printf("RETURN");
    break;

  case T_ASOMA:
    printf("OP A SOMA");
    break;

  case T_ASUBT:
    printf("OP A SUBTRACAO");
    break;

  case T_AMULT:
    printf("OP A MULTIPLICAO");
    break;

  case T_ADIV:
    printf("OP A DIVISAO");
    break;

  case T_LMENOR:
    printf("OP L MENOR");
    break;

  case T_LMAIOR:
    printf("OP L MAIOR");
    break;

  case T_LLE:
    printf("OP L MENOR IGUAL");
    break;

  case T_LGE:
    printf("OP L MAIOR IGUAL");
    break;

  case T_LEQ:
    printf("OP L IGUAL");
    break;

  case T_LNE:
    printf("OP L DIFERENTE");
    break;

  case T_LAND:
    printf("OP L E");
    break;

  case T_LOR:
    printf("OP L OU");
    break;

  case T_LNEG:
    printf("OP L NEGACAO");
    break;

  case T_ANEG:
    printf("OP A NEGATIVO");
    break;

  case T_IDENTIFICADOR:
    printf("IDENTIFICADOR");
    break;

  case T_LITERAL:
    printf("LITERAL");
    break;
  }
}
