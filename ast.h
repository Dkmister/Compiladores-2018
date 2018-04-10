#include "hash.h"

typedef struct ast_node{
  int type;
  hash_node* hash_pointer;
  struct ast_node* son[4];
}AST;

ast_node* main_node;

ast_node* new_ast(int type, hash_node* hash_pointer, ast_node* son1, ast_node* son2, ast_node* son3, ast_node* son4);

ast_node* add_node(ast_node* father, ast_node* son);

void ast_print(ast_node* printme);
