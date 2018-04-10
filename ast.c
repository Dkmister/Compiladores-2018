#include "ast.h"	

AST* new_ast(int type, HASH* hash_pointer, AST* son1, AST* son2, AST* son3, AST* son4);

AST* add_node(AST* father, AST* son);

void ast_print(AST* printme);
