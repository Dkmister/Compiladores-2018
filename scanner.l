/// Diego Dasso Migotto 00242243
/// Vilmar Neto

%{
#include "hash.h"
#include "tokens.h"
#include "aux.h"
%}

%option yylineno

%%

%%

int getLineNumber(void) { return yylineno; }
