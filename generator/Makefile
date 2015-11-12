all:
	yacc -d hot.y
	gcc -c y.tab.c
	lex hot.l
	gcc -c lex.yy.c
	gcc y.tab.o lex.yy.o -ll -o hot-parser.out
	./hot-parser.out test.hot
