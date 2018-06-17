#include "tac.h"

TAC* tacCreate(int type, HASH* res, HASH *op1, HASH *op2)
{
  TAC*newtac=0;
  newtac = (TAC*) calloc(1,sizeof(TAC));
  newtac->type = type;
  newtac->res = res;
  newtac->op1 = op1;
  newtac->op2 = op2;
  newtac->prev = 0;
  newtac->next = 0;
  return newtac;

}
