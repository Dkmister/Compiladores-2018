/* Diego Dasso Migotto 00242243
   Vilmar Neto         00242276*/

%{
#include "main.h"
#include "hash.h"
#include "ast.h"
int yydebug = 1;

extern int yyparse(void);
extern AST* main_node;

%}

%union {
  HASH* node;
  AST* ast;
}

%define parse.error verbose
%defines

/* Declaracao de tokens */

%token KW_CHAR
%token KW_INT
%token KW_FLOAT
%token KW_IF
%token KW_THEN
%token KW_ELSE
%token KW_WHILE
%token KW_FOR
%token KW_TO
%token KW_READ
%token KW_RETURN
%token KW_PRINT

%token OPERATOR_LE
%token OPERATOR_GE
%token OPERATOR_EQ
%token OPERATOR_NE
%token OPERATOR_AND
%token OPERATOR_OR

%token TK_IDENTIFIER
%token LIT_INTEGER
%token LIT_REAL
%token LIT_CHAR
%token LIT_STRING
%token TOKEN_ERROR

%type<node> LIT_INTEGER LIT_REAL LIT_CHAR LIT_STRING TK_IDENTIFIER

%type<ast> Codigo Declaracoes De_Globais De_Funcoes De_Glo_Var_Simples De_Glo_Var_Vetor 
%type<ast> Fun_Cabecalho Fun_Corpo Fun_Parametros Fun_Com_Parametros Parametro Valor Valores Bloco Lista_Comandos Comando_Simples 
%type<ast> Expressao Atribuicao Operando Fun_Chamada Fun_Cha_Parametros Fun_Cha_Com_Parametros Cha_Parametro If If_Else While For 
%type<ast> Read Print Return Identificador Lista_Print Printavel

%left OPERATOR_AND OPERATOR_OR

%left OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE

%left '<' '>' '!'

%left '*' '/'  

%left '+' '-' 

%right KW_THEN KW_ELSE

%%

/* Linguagem lang182 */


Codigo: 			{ $$ = new_ast(T_PROGRAMA); main_node = $$; }
Codigo: Codigo Declaracoes	{ $$ = $1; list_son($1, $2); }

Declaracoes: De_Globais';'	{ $$ = $1; }
Declaracoes: De_Funcoes		{ $$ = $1; }

/* Declaracoes Globais */

De_Globais: De_Glo_Var_Simples						{ $$ = $1; }
De_Glo_Var_Simples: Tipo Identificador '=' Valor			{ $$ = new_ast(T_GLOBALS); $$->son1 = $2; $$->son2 = $4; }
De_Glo_Var_Simples: Tipo '#'Identificador '=' Valor			{ $$ = new_ast(T_GLOBALP); $$->son1 = $3; $$->son2 = $5; }

De_Globais: De_Glo_Var_Vetor						{ $$ = $1; }
De_Glo_Var_Vetor: Tipo Identificador'['LIT_INTEGER']'':' Valores	{ $$ = new_ast(T_GLOBALV); $$->son1 = $2; $$->son1->son1 = new_ast(T_LITERAL); $$->son2 = $7; }
De_Glo_Var_Vetor: Tipo Identificador'['LIT_INTEGER']'			{ $$ = new_ast(T_GLOBALV); $$->son1 = $2; $$->son1->son1 = new_ast(T_LITERAL);; }

/* Declaracoes Funcoes + Chamada Funcoes */

De_Funcoes: Fun_Cabecalho Fun_Corpo			{ $$ = new_ast(T_FUNCAO_D); $$->son1 = $1; $$->son2 = $2; }

Fun_Cabecalho: Tipo Identificador '('Fun_Parametros')'	{ $$ = $2; $$->son1 = $4; }
Fun_Parametros: 					{ $$ = NULL; }
Fun_Parametros: Fun_Com_Parametros			{ $$ = $1; }
Fun_Com_Parametros: Parametro				{ $$ = $1; }
Fun_Com_Parametros: Fun_Com_Parametros','Parametro	{ $$ = $1; list_son($1, $3); }
Parametro: Tipo Identificador				{ $$ = $2; }

Fun_Corpo: Bloco					{ $$ = $1; }

Fun_Chamada: Identificador'('Fun_Cha_Parametros')'		{ $$ = new_ast(T_FUNCAO_C); $$->son1 = $1; $$->son1->son1 = $3; }
Fun_Cha_Parametros:						{ $$ = NULL; }
Fun_Cha_Parametros: Fun_Cha_Com_Parametros			{ $$ = $1; }
Fun_Cha_Com_Parametros: Cha_Parametro				{ $$ = $1; }
Fun_Cha_Com_Parametros: Fun_Cha_Com_Parametros','Cha_Parametro	{ $$ = $1; list_son($1, $3); }
Cha_Parametro: Expressao					{ $$ = $1; }

/* Comando_Simples */

Lista_Comandos: Comando_Simples				{ $$ = $1; }
Lista_Comandos: Lista_Comandos';' Comando_Simples	{ $$ = $1; if($$ != NULL) list_son($1, $3); else $$ = $3; }

Comando_Simples: 		{ $$ = NULL; }
Comando_Simples: Bloco		{ $$ = $1; }
Comando_Simples: Atribuicao	{ $$ = $1; }
Comando_Simples: If		{ $$ = $1; }
Comando_Simples: If_Else	{ $$ = $1; }
Comando_Simples: While		{ $$ = $1; }
Comando_Simples: For		{ $$ = $1; }
Comando_Simples: Read		{ $$ = $1; }
Comando_Simples: Print		{ $$ = $1; }
Comando_Simples: Return		{ $$ = $1; }

Bloco: '{' Lista_Comandos '}'	{ $$ = new_ast(T_BLOCO); $$->son1 = $2; }

Atribuicao: Identificador '=' Expressao			{ $$ = new_ast(T_ATRIBUICAO); $$->son1 = $1; $$->son3 = $3; }
Atribuicao: Identificador'['Expressao']' '=' Expressao	{ $$ = new_ast(T_ATRIBUICAO); $$->son1 = $1; $$->son1->son1 = $3; $$->son3 = $6; }

If: KW_IF '(' Expressao ')' KW_THEN Comando_Simples	{ $$ = new_ast(T_IF); $$->son1 = $3; $$->son2 = $6; }

If_Else: KW_IF '(' Expressao ')' KW_THEN Comando_Simples KW_ELSE Comando_Simples	{ $$ = new_ast(T_IFELSE); $$->son1 = $3; $$->son2 = $6; $$->son3 = $8; }

While: KW_WHILE '(' Expressao ')' Comando_Simples	{ $$ = new_ast(T_WHILE); $$->son1 = $3; $$->son2 = $5; }

For: KW_FOR '(' Identificador '=' Expressao KW_TO Expressao ')' Comando_Simples 
							{ $$ = new_ast(T_FOR); $$->son1 = $3; $$->son2 = $5; $$->son3 = $7; $$->son4 = $9; }

Read: KW_READ Identificador	{ $$ = new_ast(T_READ); $$->son1 = $2; }

Print: KW_PRINT Lista_Print		{ $$ = new_ast(T_PRINT); $$->son1 = $2; }
Lista_Print: Printavel			{ $$ = $1; }
Lista_Print: Lista_Print Printavel	{ $$ = $1; list_son($1, $2); }
Printavel: Expressao			{ $$ = $1; }
Printavel: LIT_STRING			{ $$ = $$ = new_ast(T_LITERAL); $$->hash_pointer = $1; }

Return: KW_RETURN Expressao		{ $$ = new_ast(T_RETURN); $$->son1 = $2; }

/* Expressoes */
Expressao: Operando		{ $$ = $1; }
Expressao: '(' Expressao ')'	{ $$ = $2; }

Expressao: Expressao '+' Expressao 		{ $$ = new_ast(T_ASOMA); $$->son1 = $1; $$->son2 = $3; }
Expressao: Expressao '-' Expressao		{ $$ = new_ast(T_ASUBT); $$->son1 = $1; $$->son2 = $3; }
Expressao: Expressao '*' Expressao		{ $$ = new_ast(T_AMULT); $$->son1 = $1; $$->son2 = $3; }
Expressao: Expressao '/' Expressao		{ $$ = new_ast(T_ADIV); $$->son1 = $1; $$->son2 = $3; }
Expressao: Expressao '<' Expressao		{ $$ = new_ast(T_LMENOR); $$->son1 = $1; $$->son2 = $3; }
Expressao: Expressao '>' Expressao		{ $$ = new_ast(T_LMAIOR); $$->son1 = $1; $$->son2 = $3; }
Expressao: Expressao OPERATOR_LE Expressao	{ $$ = new_ast(T_LLE); $$->son1 = $1; $$->son2 = $3; }
Expressao: Expressao OPERATOR_GE Expressao	{ $$ = new_ast(T_LGE); $$->son1 = $1; $$->son2 = $3; }
Expressao: Expressao OPERATOR_EQ Expressao	{ $$ = new_ast(T_LEQ); $$->son1 = $1; $$->son2 = $3; }
Expressao: Expressao OPERATOR_NE Expressao	{ $$ = new_ast(T_LNE); $$->son1 = $1; $$->son2 = $3; }
Expressao: Expressao OPERATOR_AND Expressao	{ $$ = new_ast(T_LAND); $$->son1 = $1; $$->son2 = $3; }
Expressao: Expressao OPERATOR_OR Expressao	{ $$ = new_ast(T_LOR); $$->son1 = $1; $$->son2 = $3; }
Expressao: '!'Expressao				{ $$ = new_ast(T_LNEG); $$->son1 = $2; }
Expressao: '(''-'Expressao')'			{ $$ = new_ast(T_ANEG); $$->son1 = $3; }

Operando: LIT_INTEGER			{ $$ = new_ast(T_LITERAL); $$->hash_pointer = $1; }
Operando: LIT_CHAR			{ $$ = new_ast(T_LITERAL); $$->hash_pointer = $1; }
Operando: Identificador			{ $$ = $1; }
Operando: '#'TK_IDENTIFIER		{ $$ = new_ast(T_IDENTIFIC_D); $$->hash_pointer = $2; }
Operando: '&'TK_IDENTIFIER		{ $$ = new_ast(T_IDENTIFIC_R); $$->hash_pointer = $2; }
Operando: Identificador'['Expressao']'	{ $$ = $1; $$->son1 = $3; }
Operando: Fun_Chamada			{ $$ = $1; }

/* Tipos */
Tipo: KW_CHAR
Tipo: KW_INT
Tipo: KW_FLOAT

/* Literais */
Valores: Valor		{ $$ = $1; }
Valores: Valores Valor	{ $$ = $1; list_son($1, $2); }

Valor: LIT_INTEGER	{ $$ = new_ast(T_LITERAL); $$->hash_pointer = $1; }
Valor: LIT_REAL		{ $$ = new_ast(T_LITERAL); $$->hash_pointer = $1; }
Valor: LIT_CHAR		{ $$ = new_ast(T_LITERAL); $$->hash_pointer = $1; }
Valor: LIT_STRING	{ $$ = new_ast(T_LITERAL); $$->hash_pointer = $1; }

Identificador: TK_IDENTIFIER	{ $$ = new_ast(T_IDENTIFICADOR); $$->hash_pointer = $1; }


