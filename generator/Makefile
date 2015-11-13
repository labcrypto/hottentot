all:
	yacc -d hot.y
	g++ -c y.tab.c
	flex hot.l
	g++ -c lex.yy.c
	g++ -c shared.cc
	g++ y.tab.o lex.yy.o shared.o -lfl -ll -o hot-parser.out
	./hot-parser.out test.hot
