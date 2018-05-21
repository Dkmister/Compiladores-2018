#include <stdio.h>
#include "ast.h"
#include "hash.h"
#include "aux.h"

void set_declarations(AST* node);

void check_expression(AST* node);

void check_command(AST* node);

void type_check(int type1, int type2);

void check_int(AST* node);

void check_returned();

int type_expression(int type1, int type2);

void type_vector(AST* node, int can_int, int can_float, int can_char, int can_string);
