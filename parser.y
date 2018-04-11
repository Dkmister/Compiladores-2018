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

%type<ast> Codigo Declaracoes De_Globais De_Funcoes De_Glo_Var_Simples De_Glo_Var_Vetor Fun_Cabecalho Fun_Corpo Fun_Parametros Fun_Com_Parametros Parametro Valor Valores Bloco Lista_Comandos Comando_Simples

%left OPERATOR_AND OPERATOR_OR

%left OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE

%left '<' '>' '!'

%left '*' '/'  

%left '+' '-'

%left KW_THEN

%left KW_ELSE

%left TK_IDENTIFIER

%left '[' '(' 

%%

/* Linguagem lang182 */


Codigo: 			{ $$ = new_ast(T_PROGRAMA); main_node = $$; }
Codigo: Codigo Declaracoes	{ $$ = $1; list_son($1, $2); }

Declaracoes: De_Globais';'	{ $$ = $1; }
Declaracoes: De_Funcoes		{ $$ = $1; }

/* Declaracoes Globais */

De_Globais: De_Glo_Var_Simples						{ $$ = $1; }
De_Glo_Var_Simples: Tipo TK_IDENTIFIER '=' Valor			{ $$ = new_ast(T_GLOBALS); $$->son1 = new_ast(T_IDENTIFICADOR); $$->son3 = $4; }
De_Glo_Var_Simples: Tipo '#'TK_IDENTIFIER '=' Valor			{ $$ = new_ast(T_GLOBALP); $$->son1 = new_ast(T_IDENTIFICADOR); $$->son3 = $5; }

De_Globais: De_Glo_Var_Vetor						{ $$ = $1; }
De_Glo_Var_Vetor: Tipo TK_IDENTIFIER'['LIT_INTEGER']'':' Valores	
				{ $$ = new_ast(T_GLOBALV); $$->son1 = new_ast(T_IDENTIFICADOR); $$->son2 = new_ast(T_LITERAL); $$->son3 = $7; }
De_Glo_Var_Vetor: Tipo TK_IDENTIFIER'['LIT_INTEGER']'	
				{ $$ = new_ast(T_GLOBALV); $$->son1 = new_ast(T_IDENTIFICADOR); $$->son2 = new_ast(T_LITERAL);; }

/* Declaracoes Funcoes + Chamada Funcoes */

De_Funcoes: Fun_Cabecalho Fun_Corpo			{ $$ = new_ast(T_FUNCAO_D); $$->son1 = $1; $$->son2 = $1->son1; $1->son1 = NULL; $$->son3 = $2; }

Fun_Cabecalho: Tipo TK_IDENTIFIER '('Fun_Parametros')'	{ $$ = new_ast(T_IDENTIFICADOR); $$->son1 = $4; }
Fun_Parametros: 					{ $$ = NULL; }
Fun_Parametros: Fun_Com_Parametros			{ $$ = $1; }
Fun_Com_Parametros: Parametro				{ $$ = $1; }
Fun_Com_Parametros: Fun_Com_Parametros','Parametro	{ $$ = $1; list_son($1, $3); }
Parametro: Tipo TK_IDENTIFIER				{ $$ = new_ast(T_IDENTIFICADOR); }

Fun_Corpo: Bloco					{ $$ = $1; }

Fun_Chamada: TK_IDENTIFIER'('Fun_Cha_Parametros')'
Fun_Cha_Parametros:
Fun_Cha_Parametros: Fun_Cha_Com_Parametros
Fun_Cha_Com_Parametros: Cha_Parametro
Fun_Cha_Com_Parametros: Fun_Cha_Com_Parametros','Cha_Parametro
Cha_Parametro: Expressao

/* Comando_Simples */

Lista_Comandos: Comando_Simples
Lista_Comandos: Lista_Comandos';' Comando_Simples

Comando_Simples: 		
Comando_Simples: Bloco
Comando_Simples: Atribuicao
Comando_Simples: If
Comando_Simples: If_Else 
Comando_Simples: While
Comando_Simples: For
Comando_Simples: Read
Comando_Simples: Print
Comando_Simples: Return

Bloco: '{' Lista_Comandos '}' 								{ $$ = new_ast(T_BLOCO); $$->son1 = $2; }

Atribuicao: TK_IDENTIFIER '=' Expressao
Atribuicao: TK_IDENTIFIER'['Expressao']' '=' Expressao

If: KW_IF '(' Expressao ')' KW_THEN Comando_Simples

If_Else: KW_IF '(' Expressao ')' KW_THEN Comando_Simples KW_ELSE Comando_Simples

While: KW_WHILE '(' Expressao ')' Comando_Simples

For: KW_FOR '(' TK_IDENTIFIER '=' Expressao KW_TO Expressao ')' Comando_Simples

Read: KW_READ TK_IDENTIFIER

Print: KW_PRINT Lista_Print
Lista_Print: Printavel
Lista_Print: Lista_Print Printavel
Printavel: Expressao
Printavel: LIT_STRING

Return: KW_RETURN Expressao

/* Expressoes */
Expressao: Operando
Expressao: '(' Expressao ')'

Expressao: Expressao '+' Expressao
Expressao: Expressao '-' Expressao
Expressao: Expressao '*' Expressao
Expressao: Expressao '/' Expressao
Expressao: Expressao '<' Expressao
Expressao: Expressao '>' Expressao
Expressao: Expressao OPERATOR_LE Expressao
Expressao: Expressao OPERATOR_GE Expressao
Expressao: Expressao OPERATOR_EQ Expressao
Expressao: Expressao OPERATOR_NE Expressao
Expressao: Expressao OPERATOR_AND Expressao
Expressao: Expressao OPERATOR_OR Expressao
Expressao: '!'Expressao
Expressao: '(''-'Expressao')'

Operando: LIT_INTEGER
Operando: LIT_CHAR
Operando: TK_IDENTIFIER
Operando: '#'TK_IDENTIFIER
Operando: '&'TK_IDENTIFIER
Operando: TK_IDENTIFIER'['Expressao']'
Operando: Fun_Chamada

/* Tipos */
Tipo: KW_CHAR
Tipo: KW_INT
Tipo: KW_FLOAT

/* Literais */
Valores: Valor { $$ = $1; }
Valores: Valores Valor { $$ = $1; list_son($1, $2); }

Valor: LIT_INTEGER	{ $$ = new_ast(T_LITERAL); $$->hash_pointer = $1; }
Valor: LIT_REAL		{ $$ = new_ast(T_LITERAL); $$->hash_pointer = $1; }
Valor: LIT_CHAR		{ $$ = new_ast(T_LITERAL); $$->hash_pointer = $1; }
Valor: LIT_STRING	{ $$ = new_ast(T_LITERAL); $$->hash_pointer = $1; }




