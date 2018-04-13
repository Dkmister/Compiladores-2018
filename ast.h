#ifndef __ast__
#include "hash.h"
#include "stdio.h"
#include "stdlib.h"
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
#define T_IDENTIFIC_D	31
#define T_IDENTIFIC_R	32

#define NOT_VAR		-1
#define CHAR_VAR	1
#define INT_VAR		2
#define FLOAT_VAR	3

typedef struct ast_node{
  int type;
  int var_type;
  HASH* hash_pointer;
  struct ast_node* son1;
  struct ast_node* son2;
  struct ast_node* son3;
  struct ast_node* son4;
  struct ast_node* son5;
}AST;

AST* main_node;

AST* new_ast(int type);

AST* new_ident_ast(HASH* pointer);

void list_son(AST* father, AST* son);

void ast_print();

void node_print(AST* printme, int level);

void program_to_file(char *filename);

void node_tf(AST* node, int level, FILE *fp);

void identificador_tf(AST* node, FILE *fp);

void valor_tf(AST* node, FILE *fp);

void lista_tf(AST* node, FILE *fp);

void print_name(int type);

#endif
