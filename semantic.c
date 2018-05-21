#include "semantic.h"
/*
Vilmar: Diego, ao inves de hash_pointer o sor usava symbol no codigo
Tem nas fotos que te passei, da uma olhada.
To meio confuso, mas essa vai ser minha contribuicao, se for util de alguma forma.

*/

int return_type = 0;
int returned = 0;

void set_declarations(AST* node)
{

  switch (node->type) {

  case T_GLOBALS:
    if (node->son1->hash_pointer->type == LT_IDENT)
    {
      node->son1->hash_pointer->type = VAR_S;
      node->son1->hash_pointer->data_type = node->son1->var_type;
      type_check(node->son1->hash_pointer->data_type, node->son2->hash_pointer->type);
    } else
      semanticError("Identifier already declared;");
    break; 

  case T_GLOBALP:
    if (node->son1->hash_pointer->type == LT_IDENT)
    {
      node->son1->hash_pointer->type = VAR_S;
      node->son1->hash_pointer->data_type = node->son1->var_type;
      type_check(node->son1->hash_pointer->data_type, node->son2->hash_pointer->type);
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
      return_type = node->son1->var_type;
      returned = 0;
    } else
      semanticError("Identifier already declared;");
    break;

  case T_IDENTIFICADOR:
    if (node->hash_pointer->type == LT_IDENT)
    {
      node->hash_pointer->type = VAR_S;
      node->hash_pointer->data_type = node->var_type;
      node->hash_pointer->scoped = 1;
    } else
      semanticError("Identifier already declared;");
    break; 
    

  }

}

void check_expression(AST* node)
{

  int left_type = 0;
  int right_type = 0;
  if (node->son2 != NULL)
    switch (node->son1->type)
    {

    case T_LITERAL:
      left_type = node->son1->hash_pointer->type;
      break;

    case T_IDENTIFICADOR:
    case T_IDENTIFIC_D:
    case T_IDENTIFIC_R:
      left_type = node->son1->hash_pointer->data_type;
      break;

    case T_FUNCAO_C:
      left_type = node->son1->son1->hash_pointer->data_type;
      break;

    default:
      left_type = node->son2->exp_type;
      break;

    }

  if (node->son2 != NULL)
    switch (node->son2->type)
    {

    case T_LITERAL:
      right_type = node->son2->hash_pointer->type;
      break;

    case T_IDENTIFICADOR:
    case T_IDENTIFIC_D:
    case T_IDENTIFIC_R:
      right_type = node->son2->hash_pointer->data_type;
      break;

    case T_FUNCAO_C:
      right_type = node->son2->son1->hash_pointer->data_type;
      break;

    default:
      right_type = node->son2->exp_type;
      break;

    }

  switch (node->type) {

  case T_ASOMA:
  case T_ASUBT:
  case T_AMULT:
  case T_ADIV:
    node->exp_type = type_expression(left_type, right_type);
    
  case T_LMENOR:
  case T_LMAIOR:
  case T_LLE:
  case T_LGE:
  case T_LEQ:
  case T_LNE:
  case T_LAND:
  case T_LOR:
    node->exp_type = type_expression(left_type, right_type);
    break;

  case T_ANEG:
  case T_LNEG:
    node->exp_type = left_type;
    break;


  case T_IDENTIFICADOR:
  case T_IDENTIFIC_D:
  case T_IDENTIFIC_R:
    if (node->hash_pointer->type == LT_IDENT)
    {
      semanticError("Identifier not declared;");
    }
    break;

  }

}

void check_command(AST *node)
{

  int right_type = 0;

  switch (node->type) {

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
    switch (node->son2->type)
    {
      case T_LITERAL:
        right_type = node->son2->hash_pointer->type;
        break;

      case T_IDENTIFICADOR:
      case T_IDENTIFIC_D:
      case T_IDENTIFIC_R:
        right_type = node->son2->hash_pointer->data_type;
        break;

      case T_FUNCAO_C:
        right_type = node->son2->son1->hash_pointer->data_type;
        break;

      default:
        right_type = node->son2->exp_type;
        break;

    }
    if (node->son1->hash_pointer->type == LT_IDENT)
    {
      semanticError("Identifier not declared;");
    } else if (node->son1->hash_pointer->type == VAR_F)
      semanticError("Trying to assign to a function;");
    else if (node->son1->hash_pointer->type == VAR_S)
      type_check(node->son1->hash_pointer->data_type, right_type);
    else if (node->son1->hash_pointer->type == VAR_V)
    {
      type_check(node->son1->hash_pointer->data_type, right_type);
      check_int(node->son1->son1);
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
    switch (node->son1->type)
    {
      case T_LITERAL:
        type_check(return_type, node->son1->hash_pointer->type);
        break;

      case T_IDENTIFICADOR:
      case T_IDENTIFIC_D:
      case T_IDENTIFIC_R:
        type_check(return_type, node->son1->hash_pointer->data_type);
        break;

      case T_FUNCAO_C:
        type_check(return_type, node->son1->son1->hash_pointer->data_type);
        break;

      default:
        type_check(return_type, node->son1->exp_type);
        break;

    }
    returned = 1;
    break;

  }

}

void type_check(int type1, int type2)
{
  printf("\n1: %d, 2: %d\n", type1, type2);
  if ((type1 != type2) && !(((type1 == CHAR_VAR) && (type2 == INT_VAR)) || ((type2 == CHAR_VAR) && (type1 == INT_VAR))))
    semanticError("Types do not match;");
}

void check_int(AST* node)
{
  switch (node->type)
  {
    case T_LITERAL:
      type_check(node->hash_pointer->type, LT_INT);
      break;

    case T_IDENTIFICADOR:
    case T_IDENTIFIC_D:
    case T_IDENTIFIC_R:
      type_check(node->hash_pointer->data_type, LT_INT);
      break;

    case T_FUNCAO_C:
      type_check(node->son1->hash_pointer->data_type, LT_INT);
      break;
  }

}

void check_returned()
{
  if (!returned)
    semanticError("Function didn't return any value;");
}

int type_expression(int type1, int type2)
{
  if (type1 == type2)
    return type1;

  if ((type1 == LT_FLOAT) || (type2 == LT_FLOAT))
    return LT_FLOAT;
  else if ((type1 == LT_INT) || (type2 == LT_INT))
    return LT_INT;
  else
    return LT_CHAR;
}

void type_vector(AST* node, int can_int, int can_float, int can_char, int can_string)
{

  if (node != NULL)
  {
    if ( ((node->hash_pointer->type == LT_INT) && can_int) || ((node->hash_pointer->type == LT_FLOAT) && can_float) || ((node->hash_pointer->type == LT_CHAR) && can_char) || ((node->hash_pointer->type == LT_STRING) && can_string))
      type_vector(node->son5, can_int, can_float, can_char, can_string);
    else
      semanticError("Types do not match;");
  } else return;
}

