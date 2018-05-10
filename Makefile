#
# UFRGS - Compiladores B - Marcelo Johann - 2009/2 - Etapa 3
#
# Makefile for three compiler calls
# Read the comments on Makefile2. All of them apply here too.
# But now the hash table is compiled in a separate gcc call
# Therefore, there must be a header of it to be included in scanner.l
#

etapa4: parser.tab.o lex.yy.o main.o hash.o aux.o ast.o semantic.o
	gcc -o etapa4 parser.tab.o lex.yy.o main.o hash.o aux.o ast.o semantic.o
main.o: main.c
	gcc -c main.c
ast.o: ast.c
	gcc -c ast.c
hash.o: hash.c
	gcc -c hash.c
aux.o: aux.c
	gcc -c aux.c
lex.yy.o: lex.yy.c
	gcc -c lex.yy.c
lex.yy.c: scanner.l
	flex --header-file=lex.yy.h scanner.l
parser.tab.o: parser.tab.c
	gcc -c parser.tab.c
parser.tab.c: parser.y
	bison -d -v parser.y
semantic: semantic.c
	gcc  -c semantic.c
clean:
	rm *.o lex.yy.c etapa3 parser.tab.c parser.tab.h parser.output lex.yy.h saida.txt
