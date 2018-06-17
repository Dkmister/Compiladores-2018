#include "tac.h"

#define TAC_SYMBOL 1
#define TAC_ADD 2
#define TAC_SUB 3
#define TAC_MUL 4
#define TAC_DIV 5
#define TAC_ASSIGN 6



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


TAC* tacPrintSingle(TAC*tac)
{
  if(!tac) return;
  fprintf(stderr,"TAC(");
  switch(tac->type)
  {
    case TAC_SYMBOL:  fprintf(stderr,"TAC_SYMBOL");break;
    case TAC_ADD:  fprintf(stderr,"TAC_ADD");break;
    case TAC_SUB:  fprintf(stderr,"TAC_SUB");break;
    case TAC_MUL:  fprintf(stderr,"TAC_MUL");break;
    case TAC_DIV:  fprintf(stderr,"TAC_DIV");break;
    case TAC_ASSIGN:  fprintf(stderr,"TAC_ASSIGN");break;
    default: fprintf(stderr,"TAC_UNKNOWN");break;     
  }
  if(tac->res) fprintf(stderr,"%s",tac->res->text);
  else fprintf(stderr,",0");
  if(tac->op1) fprintf(stderr,"%s",tac->op1->text);
  else fprintf(stderr,",0");
  if(tac->op2) fprintf(stderr,"%s",tac->op2->text);
  else fprintf(stderr,",0");
  
  fprintf(stderr,")\n");
}


TAC* tacPrintBack(TAC*tac)
{
  if(!tac) return;
  tacPrintSingle(tac);
  tacPrintBack(tac->prev);
}
