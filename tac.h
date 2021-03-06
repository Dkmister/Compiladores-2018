#ifndef TAC_HEADER
#include "hash.h"
#include "ast.h"
#include <stdio.h>
#define TAC_HEADER


typedef struct tac{
  int type;
  HASH *res;
  HASH *op1;
  HASH *op2;
  struct tac *prev;
  struct tac *next;
}TAC;


TAC *main_code;
TAC *tacCreate(int type, HASH *res, HASH *op1,HASH *op2);
TAC *tacPrintSingle(TAC *tac);
TAC *tacPrintBack(TAC*tac);
TAC *tacJoin(TAC*l1,TAC*l2);
TAC *codeGenerator(AST* node);

#endif
