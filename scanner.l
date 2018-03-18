/// Diego Dasso Migotto 00242243
/// Vilmar Neto

%{
#include "hash.h"
#include "tokens.h"
#include "aux.h"
%}

%option yylineno

%%

/// Palavras reservadas
char { return KW_CHAR; } 
int { return KW_INT; }
float { return KW_FLOAT; }
if { return KW_IF; }
then { return KW_THEN; }
else { return KW_ELSE; }
while { return KW_WHILE; }
for { return KW_FOR; }
read { return KW_READ; }
print { return KW_PRINT; }
return { return KW_RETURN; }

/// Caracteres especiais
(,|;|:|\(|\)|\[|\]|\{|\}|\+|\-|\*|\/|<|>|=|!|&|\$|\%|#) { return (int) yytext[0]; }

%%

int getLineNumber(void) { return yylineno; }
