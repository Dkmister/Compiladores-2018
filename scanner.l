/* Diego Dasso Migotto 00242243
   Vilmar Neto         00242276*/

%{
#include "hash.h"
#include "aux.h"
#include "main.h"
#include "parser.tab.h"
%}

%option yylineno

%%

\n

 /* Palavras reservadas */
char { return KW_CHAR; }
int { return KW_INT; }
float { return KW_FLOAT; }
if { return KW_IF; }
then { return KW_THEN; }
else { return KW_ELSE; }
while { return KW_WHILE; }
for { return KW_FOR; }
to { return KW_TO; }
read { return KW_READ; }
print { return KW_PRINT; }
return { return KW_RETURN; }

 /* Caracteres especiais */
(,|;|:|\(|\)|\[|\]|\{|\}|\+|\-|\*|\/|<|>|=|!|&|\$|\%|#) { return (int) yytext[0]; }

 /* Operadores compostos */
\<= { return OPERATOR_LE; }
\>= { return OPERATOR_GE; }
== { return OPERATOR_EQ; }
!= { return OPERATOR_NE; }
&& { return OPERATOR_AND; }
\|\| { return OPERATOR_OR; }

 /* Literais */
[0-9]+ { hashInsert(LT_INT, yytext); return LIT_INTEGER; }
[0-9]+\.[0-9]+ { hashInsert(LT_FLOAT, yytext); return LIT_REAL; }
'.' { hashInsert(LT_CHAR, yytext); return LIT_CHAR; }
\"(\\.|[^"])*\" { hashInsert(LT_STRING, yytext); return LIT_STRING; }

 /* Identificadores */
([a-z]|[A-Z]|_)([a-z]|[A-Z]|_|[0-9])* { hashInsert(LT_IDENT, yytext); return TK_IDENTIFIER; }

 /* Comentarios e Espacos */

"//".*
[ \t\r]+
"/*"(.|\n)*"*/"

 /* Erro */

. { return TOKEN_ERROR; }

%%
#include "main.h"

// Called when reach eof, set control var to 0
int yywrap(void) { foundEof(); return 1; }
