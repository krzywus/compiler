
both: flex.lex bison.y
	$(MAKE) bison
	$(MAKE) flex
	gcc -g bin/lex.yy.c bin/bison.yy.h -ll -lm
	mv a.out bin/a.out

lex.yy.c: flex.lex
	make flex

bison.yy.h: bison.y
	make bison

flex:
		flex flex.lex
		mv lex.yy.c bin/lex.yy.c

bison:
		bison -o bin/bison.yy.h bison.y

run:
	$(MAKE) bison
	$(MAKE) flex
	gcc -g bin/lex.yy.c bin/bison.yy.h -ll -lm
	# mv bison.yy.h.gch bin/bison.yy.h.gch
	mv a.out bin/a.out
	./bin/a.out
