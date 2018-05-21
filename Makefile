#
# UFRGS - Compiladores B - Marcelo Johann - 2009/2 - Etapa 3
#
# Makefile for three compiler calls
# Read the comments on Makefile2. All of them apply here too.
# But now the hash table is compiled in a separate gcc call
# Therefore, there must be a header of it to be included in scanner.l
#

etapa4: parser.tab.o lex.yy.o main.o hash.o aux.o ast.o semantic.o
	gcc -g -o etapa4 parser.tab.o lex.yy.o main.o hash.o aux.o ast.o semantic.o
main.o: main.c
	gcc -g -c main.c
semantic.o: semantic.c
	gcc -g -c semantic.c
ast.o: ast.c
	gcc -g -c ast.c
hash.o: hash.c
	gcc -g -c hash.c
aux.o: aux.c
	gcc -g -c aux.c
lex.yy.o: lex.yy.c
	gcc -g -c lex.yy.c
lex.yy.c: scanner.l
	flex --header-file=lex.yy.h scanner.l
parser.tab.o: parser.tab.c
	gcc -g -c parser.tab.c
parser.tab.c: parser.y
	bison -d -v parser.y
clean:
	rm *.o lex.yy.c etapa4 parser.tab.c parser.tab.h parser.output lex.yy.h saida.txt saida2.txt
