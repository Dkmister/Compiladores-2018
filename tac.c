#include "tac.h"

#define MAX_SONS 5
#define TAC_SYMBOL 1
#define TAC_ADD 2
#define TAC_SUB 3
#define TAC_MUL 4
#define TAC_DIV 5
#define TAC_ASSIGN 6
#define TAC_LABEL 7
#define TAC_BEGINFUN 8
#define TAC_ENDFUN 9
#define TAC_IFZ 10
#define TAC_JUMP 11
#define TAC_CALL 12
#define TAC_ARG 13
#define TAC_RET 14
#define TAC_PRINT 15
#define TAC_READ 16


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
  if(!tac) return 0;
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
  if(!tac) return 0;
  tacPrintSingle(tac);
  tacPrintBack(tac->prev);
}


TAC* tacJoin(TAC*l1,TAC*l2){

  TAC*aux = 0;
  if (!l1) return l2;
  if (!l2) return l1;
  for(aux = l1; aux->prev; aux = aux->prev) ;

  aux->prev = l1;
  return l2;
}

// Intermediate Code Generation

TAC *codeGenerator(AST *node){

  TAC *result = 0;
  TAC *code[MAX_SONS];

  if (!node) return 0;
  
  code[0] = codeGenerator(node->son1);
  code[1] = codeGenerator(node->son2);
  code[2] = codeGenerator(node->son3);
  code[3] = codeGenerator(node->son4);
  code[4] = codeGenerator(node->son5);


  switch(node->type){
    case T_ADIV:  result = tacJoin(code[0],tacJoin(code[1],tacCreate(TAC_DIV,0,code[0]?code[0]->res:0,code[1]?code[1]->res:0))); break;
    case T_AMULT: result = tacJoin(code[0],tacJoin(code[1],tacCreate(TAC_MUL,0,code[0]?code[0]->res:0,code[1]?code[1]->res:0))); break;
    case T_ASUBT: result = tacJoin(code[0],tacJoin(code[1],tacCreate(TAC_SUB,0,code[0]?code[0]->res:0,code[1]?code[1]->res:0))); break;
	case T_ASOMA: result = tacJoin(code[0],tacJoin(code[1],tacCreate(TAC_ADD,0,code[0]?code[0]->res:0,code[1]?code[1]->res:0))); break;
	default: result = tacJoin(tacJoin(tacJoin(tacJoin(code[1],code[1]),code[2]),code[3]),code[4]);}

  return result; }
