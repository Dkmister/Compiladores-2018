#include "semantic.h"
/*
Vilmar: Diego, ao inves de hash_pointer o sor usava symbol no codigo
Tem nas fotos que te passei, da uma olhada.
To meio confuso, mas essa vai ser minha contribuicao, se for util de alguma forma.

*/
void set_declarations(AST *node){

  switch (node->type) {

  case T_GLOBALS:
    if (node->son1->hash_pointer->type == LT_IDENT)
    {
      node->son1->hash_pointer->type = VAR_S;
      node->son1->hash_pointer->data_type = node->son1->var_type;
      type_check(node->son1->hash_pointer->data_type, node->son2->hash_pointer->type, 0);
    } else
      semanticError("Identifier already declared;");
    break; 

  case T_GLOBALP:
    if (node->son1->hash_pointer->type == LT_IDENT)
    {
      node->son1->hash_pointer->type = VAR_S;
      node->son1->hash_pointer->data_type = node->son1->var_type;
      type_check(node->son1->hash_pointer->data_type, node->son2->hash_pointer->type, 0);
    } else
      semanticError("Identifier already declared;");
    break; 

  case T_GLOBALV:
    if (node->son1->hash_pointer->type == LT_IDENT)
    {
      node->son1->hash_pointer->type = VAR_V;
      node->son1->hash_pointer->data_type = node->son1->var_type;
      int can_int = 0, can_float = 0, can_char = 0;
      switch (node->son1->hash_pointer->data_type)
      {
      case INT_VAR:
        can_int = 1;
        can_char = 1;
        break;
      case FLOAT_VAR:
        can_float = 1;
        break;
      case CHAR_VAR:
        can_int = 1;
        can_char = 1;
      }
      type_vector(node->son2, can_int, can_float, can_char, 0);
    } else
      semanticError("Identifier already declared;");
    break; 

  case T_FUNCAO_D:
    if (node->son1->hash_pointer->type == LT_IDENT)
    {
      node->son1->hash_pointer->type = VAR_F;
      node->son1->hash_pointer->data_type = node->son1->var_type;
    } else
      semanticError("Identifier already declared;");
    break; 

  case T_FUNCAO_C:
    if (node->son1->hash_pointer->type == LT_IDENT)
    {
      semanticError("Identifier not declared;");
    } else if (node->son1->hash_pointer->type != VAR_F)
      semanticError("Identifier not declared as function;");
    break;

  case T_BLOCO:
    break;

  case T_ATRIBUICAO:
    if (node->son1->hash_pointer->type == LT_IDENT)
    {
      semanticError("Identifier not declared;");
    } else if (node->son2->hash_pointer->type == LT_IDENT)
    {
      semanticError("Identifier not declared;");
    } else if (node->son1->hash_pointer->type == VAR_F)
      semanticError("Trying to assign to a function;");
    else if (node->son1->hash_pointer->type == VAR_S)
      type_check(node->son1->hash_pointer->data_type, node->son2->hash_pointer->type, node->son2->hash_pointer->data_type);
    else if (node->son1->hash_pointer->type == VAR_V)
    {
      int can_int = 0, can_float = 0, can_char = 0;
      switch (node->son1->hash_pointer->data_type)
      {
      case INT_VAR:
        can_int = 1;
        can_char = 1;
        break;
      case FLOAT_VAR:
        can_float = 1;
        break;
      case CHAR_VAR:
        can_int = 1;
        can_char = 1;
      }
      type_vector(node->son2, can_int, can_float, can_char, 0);
      type_check(node->son1->son1->hash_pointer->data_type, LT_INT, 0);
    }
    break; 

  case T_IF:
    break;

  case T_IFELSE:
    break;

  case T_WHILE:
    break;

  case T_FOR:
    break;

  case T_READ:
    break;

  case T_PRINT:
    break;

  case T_RETURN:
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
    break;

  case T_ANEG:
    break;

  case T_LNEG:
    break;

  case T_LITERAL:
    break;

  case T_IDENTIFICADOR:
    if (node->son1->hash_pointer->type == LT_IDENT)
    {
      semanticError("Identifier not declared;");
    }
    break;

  case T_IDENTIFIC_D:
    break;	

  case T_IDENTIFIC_R:
    break;

  }

}

void type_check(int type1, int type2, int type3)
{
  if ((type1 != type2) && !(((type1 == CHAR_VAR) && (type2 == INT_VAR)) || ((type2 == CHAR_VAR) && (type1 == INT_VAR))))
    if ((type1 != type3) && !(((type1 == CHAR_VAR) && (type3 == INT_VAR)) || ((type3 == CHAR_VAR) && (type1 == INT_VAR))))
      semanticError("Types do not match;");
}

void type_vector(AST *node, int can_int, int can_float, int can_char, int can_string)
{

  if (node != NULL)
  {
    if ( ((node->hash_pointer->type == LT_INT) && can_int) || ((node->hash_pointer->type == LT_FLOAT) && can_float) || ((node->hash_pointer->type == LT_CHAR) && can_char) || ((node->hash_pointer->type == LT_STRING) && can_string))
      type_vector(node->son5, can_int, can_float, can_char, can_string);
    else
      semanticError("Types do not match;");
  } else return;
}

