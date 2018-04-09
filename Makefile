#
# UFRGS - Compiladores B - Marcelo Johann - 2009/2 - Etapa 1
#
# Makefile for three compiler calls
# Read the comments on Makefile2. All of them apply here too.
# But now the hash table is compiled in a separate gcc call
# Therefore, there must be a header of it to be included in scanner.l
#

etapa1: parser.tab.o lex.yy.o main.o hash.o aux.o
	gcc -o etapa1 parser.tab.o lex.yy.o main.o hash.o aux.o
main.o: main.c
	gcc -c main.c
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
	bison -d parser.y
clean:
	rm *.o lex.yy.c etapa1 parser.tab.c parser.output parser.tab.h y.tab.c y.output lex.yy.h
