/* Diego Dasso Migotto 00242243
   Vilmar Neto         00242276*/

%{
#include "main.h"

int yydebug = 1;

%}

%define parse.error verbose

/* Declaracao de tokens */

%token KW_CHAR
%token KW_INT
%token KW_FLOAT
%token KW_IF
%token KW_THEN
%token KW_ELSE
%token KW_WHILE
%token KW_FOR
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

%%

/* Linguagem lang182 */


Codigo: 
Codigo: Codigo Declaracoes

Declaracoes: De_Globais';'
Declaracoes: De_Funcoes

/* Declaracoes Globais */

De_Globais: De_Glo_Var_Simples
De_Glo_Var_Simples: Tipo TK_IDENTIFIER OPERATOR_EQ Valor
De_Glo_Var_Simples: Tipo '#'TK_IDENTIFIER OPERATOR_EQ Valor

De_Globais: De_Glo_Var_Vetor
De_Glo_Var_Vetor: Tipo TK_IDENTIFIER'['LIT_INTEGER']'':' Valores
De_Glo_Var_Vetor: Tipo TK_IDENTIFIER'['LIT_INTEGER']'

/* Declaracoes Funcoes */

De_Funcoes: Fun_Cabecalho Fun_Corpo

Fun_Cabecalho: Tipo TK_IDENTIFIER '('Fun_Parametros')'
Fun_Parametros: 
Fun_Parametros: Fun_Com_Parametros
Fun_Com_Parametros: Parametro
Fun_Com_Parametros: Fun_Com_Parametros','Parametro
Parametro: Tipo TK_IDENTIFIER

Fun_Corpo: Bloco

/* Comando_Simples */

Lista_Comandos: Comando_Simples
Lista_Comandos: Lista_Comandos';' Comando_Simples

Comando_Simples: 
Comando_Simples: Bloco
Comando_Simples: Atribuicao
/*Comando_Simples: If
Comando_Simples: If_Else
Comando_Simples: While
Comando_Simples: For*/
Comando_Simples: Read
Comando_Simples: Print
Comando_Simples: Return

Bloco: '{' Lista_Comandos '}'

Atribuicao: TK_IDENTIFIER OPERATOR_EQ Expressao
Atribuicao: TK_IDENTIFIER'['Expressao']' OPERATOR_EQ Expressao

Read: KW_READ TK_IDENTIFIER

Print: KW_PRINT Lista_Print
Lista_Print: Printavel
Lista_Print: Lista_Print Printavel
Printavel: Expressao
Printavel: LIT_STRING

Return: KW_RETURN Expressao

/* Expressoes */
Expressao: LIT_INTEGER

/* Tipos */
Tipo: KW_CHAR
Tipo: KW_INT
Tipo: KW_FLOAT

/* Literais */
Valores: Valor
Valores: Valores Valor

Valor: LIT_INTEGER
Valor: LIT_REAL
Valor: LIT_CHAR
Valor: LIT_STRING




