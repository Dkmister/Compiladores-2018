#ifndef __ast__
#include "hash.h"
#define __ast__

#define T_PROGRAMA	0
#define T_GLOBALS	1
#define T_GLOBALP	2
#define T_GLOBALV	3
#define T_FUNCAO_D	4
#define T_FUNCAO_C	5
#define T_BLOCO		6
#define T_ATRIBUICAO	7
#define T_IF		8
#define T_IFELSE	9
#define T_WHILE		10
#define T_FOR		11
#define T_READ		12
#define T_PRINT		13
#define T_RETURN	14
#define T_ASOMA		15
#define T_ASUBT		16
#define T_AMULT		17
#define T_ADIV		18
#define T_LMENOR	19
#define T_LMAIOR	20
#define T_LLE		21
#define T_LGE		22
#define T_LEQ		23
#define T_LNE		24
#define T_LAND		25
#define T_LOR		26
#define T_LNEG		27
#define T_ANEG		28
#define T_IDENTIFICADOR	29
#define	T_LITERAL	30

typedef struct ast_node{
  int type;
  HASH* hash_pointer;
  struct ast_node* son[4];
}AST;

AST* main_node;

AST* new_ast(int type, HASH* hash_pointer, AST* son1, AST* son2, AST* son3, AST* son4);

AST* add_node(AST* father, AST* son);

void ast_print(AST* printme);

#endif
