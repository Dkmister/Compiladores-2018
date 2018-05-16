#include <stdio.h>
#include "ast.h"
#include "hash.h"
#include "aux.h"

void set_declarations(AST *node);

void type_check(int type1, int type2, int type3);

void type_vector(AST *node, int can_int, int can_float, int can_char, int can_string);
