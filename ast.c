#include "ast.h"	

AST* new_ast(int type)
{
  AST* node = malloc(sizeof(AST));
  node->type = type;
  node->var_type = NOT_VAR;
  node->exp_type = 0;
  node->hash_pointer = NULL;
  node->son1 = NULL;
  node->son2 = NULL;
  node->son3 = NULL;
  node->son4 = NULL;
  node->son5 = NULL;
}

AST* new_ident_ast(HASH* pointer)
{
  AST* node = new_ast(T_IDENTIFICADOR);
  node->hash_pointer = pointer;
  return node;
}

void list_son(AST* father, AST* son)
{
  if (father->son5 == NULL)
    father->son5 = son;
  else
    list_son(father->son5, son);
}

void ast_print()
{
  printf("\n| IMPRESSAO A PARTIR DA RAIZ DA AST |\n");
  node_print(main_node, 0);
  printf("\n\n| FIM DA IMPRESSAO |\n\n");
}

void node_print(AST* printme, int level)
{
  if (printme == NULL)
    return;

  printf("\n");
  for(int i = 0; i <= level; i++)
    printf("  ");
  printf("| ");
  print_name(printme->type);

  node_print(printme->son1, level+1);
  node_print(printme->son2, level+1);
  node_print(printme->son3, level+1);
  node_print(printme->son4, level+1);
  node_print(printme->son5, level);
}

void program_to_file(char *filename)
{
  FILE *fp;

  fp = fopen(filename, "w");
  fprintf(fp, "//File containing the generated code by decompiling the AST.\n");
  node_tf(main_node, fp);
  fclose(fp);
}

void node_tf(AST* node, FILE *fp)
{
  if (node == NULL)
    return;

  switch (node->type) {

  case T_PROGRAMA:
    node_tf(node->son5, fp);
    break;

  case T_GLOBALS:
    fprintf(fp, "\n");
    tipo_tf(node->son1, fp);
    fprintf(fp, " ");
    identificador_tf(node->son1, fp);
    fprintf(fp," = ");
    node_tf(node->son2, fp);
    fprintf(fp, ";");
    node_tf(node->son5, fp);
    break; 

  case T_GLOBALP:
    fprintf(fp, "\n");
    tipo_tf(node->son1, fp);
    fprintf(fp, " #");
    identificador_tf(node->son1, fp);
    fprintf(fp," = ");
    node_tf(node->son2, fp);
    fprintf(fp, ";");
    node_tf(node->son5, fp);
    break; 

  case T_GLOBALV:
    fprintf(fp, "\n");
    tipo_tf(node->son1, fp);
    fprintf(fp, " ");
    identificador_tf(node->son1, fp);
    if (node->son2 != NULL) {
      fprintf(fp,":");
      vetor_tf(node->son2, fp);
    }
    fprintf(fp, ";");
    node_tf(node->son5, fp);
    break; 

  case T_FUNCAO_D:
    fprintf(fp, "\n\n");
    tipo_tf(node->son1, fp);
    fprintf(fp, " ");
    node_tf(node->son1, fp);
    fprintf(fp, "(");
    if (node->son1->son2 != NULL) {
      tipo_tf(node->son1->son2, fp);
      fprintf(fp, " ");
      node_tf(node->son1->son2, fp);
      arg_tf(node->son1->son2->son5, fp);
    }
    fprintf(fp, ")");
    fprintf(fp, "\n");
    fprintf(fp, "{");
    node_tf(node->son2->son1, fp);
    fprintf(fp, "\n");
    fprintf(fp, "}");
    node_tf(node->son5, fp);
    break; 

  case T_FUNCAO_C:
    node_tf(node->son1, fp);
    fprintf(fp, "(");    
    if (node->son1->son2 != NULL) {
      node_tf(node->son1->son2, fp);
      lista_tf(node->son1->son2->son5, fp);
    }
    fprintf(fp, ")");
    break;

  case T_BLOCO:
    fprintf(fp, "\n");
    fprintf(fp, "{");
    node_tf(node->son1, fp);
    fprintf(fp, "\n");
    fprintf(fp, "};");
    node_tf(node->son5, fp);
    break;

  case T_ATRIBUICAO:
    fprintf(fp, "\n");
    node_tf(node->son1, fp);
    fprintf(fp, " = ");
    node_tf(node->son2, fp);
    fprintf(fp, ";");
    node_tf(node->son5, fp);
    break; 

  case T_IF:
    fprintf(fp, "\nif (");
    node_tf(node->son1, fp);
    fprintf(fp, ") then ");
    if (node->son2 != NULL)
      node_tf(node->son2, fp);
    else fprintf(fp, "\n;");
    node_tf(node->son5, fp);
    break;

  case T_IFELSE:
    fprintf(fp, "\nif (");
    node_tf(node->son1, fp);
    fprintf(fp, ") then ");
    node_tf(node->son2, fp);
    fprintf(fp, " \nelse "); 
    if (node->son3 != NULL)
      node_tf(node->son3, fp);
    else fprintf(fp, "\n;");
    node_tf(node->son5, fp);
    break;

  case T_WHILE:
    fprintf(fp, "\nwhile (");
    node_tf(node->son1, fp);
    fprintf(fp, ") ");
    if (node->son2 != NULL)
      node_tf(node->son2, fp);
    else fprintf(fp, "\n;");
    node_tf(node->son5, fp);
    break;

  case T_FOR:
    fprintf(fp, "\nfor (");
    node_tf(node->son1, fp);
    fprintf(fp, " = ");
    node_tf(node->son2, fp);
    fprintf(fp, " to ");
    node_tf(node->son3, fp);
    fprintf(fp, ") ");
    if (node->son4 != NULL)
      node_tf(node->son4, fp);
    else fprintf(fp, "\n;");
    node_tf(node->son5, fp);
    break;

  case T_READ:
    fprintf(fp, "\nread ");
    node_tf(node->son1, fp);
    fprintf(fp, ";");
    node_tf(node->son5, fp);
    break;

  case T_PRINT:
    fprintf(fp, "\nprint ");
    node_tf(node->son1, fp);
    lista_tf(node->son1->son5, fp);
    fprintf(fp, ";");
    node_tf(node->son5, fp);
    break;

  case T_RETURN:
    fprintf(fp, "\nreturn ");
    node_tf(node->son1, fp);
    fprintf(fp, ";");
    node_tf(node->son5, fp);
    break;

  case T_ASOMA:
  case T_ASUBT:
  case T_AMULT:
  case T_ADIV:
  case T_LMENOR:
  case T_LMAIOR:
  case T_LLE:
  case T_LGE:
  case T_LEQ:
  case T_LNE:
  case T_LAND:
  case T_LOR:
    node_tf(node->son1, fp);
    operator_tf(node, fp);
    node_tf(node->son2, fp);
    break;

  case T_ANEG:
    fprintf(fp, "-");
    node_tf(node->son1, fp);
    break;

  case T_LNEG:
    fprintf(fp, "!");
    node_tf(node->son1, fp);
    break;

  case T_LITERAL:
    valor_tf(node, fp);
    break;

  case T_IDENTIFICADOR:
    identificador_tf(node, fp);
    break;

  case T_IDENTIFIC_D:
    identificador_tf(node, fp);
    break;

  case T_IDENTIFIC_R:
    identificador_tf(node, fp);
    break;

  }
}

void tipo_tf(AST* node, FILE *fp)
{
  switch (node->var_type) {

  case NOT_VAR:
    fprintf(fp, "not_var");
    break;

  case CHAR_VAR:
    fprintf(fp, "char");
    break;

  case INT_VAR:
    fprintf(fp, "int");
    break;

  case FLOAT_VAR:
    fprintf(fp, "float");
    break;

  default:
    fprintf(fp, "error");
    break;

  }
}

void identificador_tf(AST* node, FILE *fp)
{
  switch (node->type) {
  case T_IDENTIFIC_R:
    fprintf(fp, "&");
    break;
  case T_IDENTIFIC_D:
    fprintf(fp, "#");
    break;
  }

  fprintf(fp, "%s", node->hash_pointer->text);

  if (node->son1 != NULL) {
    fprintf(fp, "[");
    node_tf(node->son1, fp);
    fprintf(fp, "]");
  }

}

void valor_tf(AST* node, FILE *fp)
{
  fprintf(fp, "%s", node->hash_pointer->text);
}

void vetor_tf(AST* node, FILE *fp)
{
  if (node == NULL)
    return;
  fprintf(fp, " ");
  node_tf(node, fp);
  vetor_tf(node->son5, fp);
}

void arg_tf(AST* node, FILE *fp)
{
  if (node == NULL)
    return;
  fprintf(fp, ", ");
  tipo_tf(node, fp);
  fprintf(fp, " ");
  identificador_tf(node, fp);
  arg_tf(node->son5, fp);
}

void lista_tf(AST* node, FILE *fp)
{
  if (node == NULL)
    return;
  fprintf(fp, ", ");
  node_tf(node, fp);
  lista_tf(node->son5, fp);
}

void operator_tf(AST* node, FILE *fp)
{
  switch (node->type) {
  case T_ASOMA:
    fprintf(fp, " + ");
    break;
  case T_ASUBT:
    fprintf(fp, " - ");
    break;
  case T_AMULT:
    fprintf(fp, " * ");
    break;
  case T_ADIV:
    fprintf(fp, " / ");
    break;
  case T_LMENOR:
    fprintf(fp, " < ");
    break;
  case T_LMAIOR:
    fprintf(fp, " > ");
    break;
  case T_LLE:
    fprintf(fp, " <= ");
    break;
  case T_LGE:
    fprintf(fp, " >= ");
    break;
  case T_LEQ:
    fprintf(fp, " == ");
    break;
  case T_LNE:
    fprintf(fp, " != ");
    break;
  case T_LAND:
    fprintf(fp, " && ");
    break;
  case T_LOR:
    fprintf(fp, " || ");
    break;
  }
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

  case T_IDENTIFIC_D:
    printf("REFERENCIA VAR");
    break;

  case T_IDENTIFIC_R:
    printf("DERREFERE PTR");
    break;
  }
}
