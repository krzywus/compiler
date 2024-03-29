
both: flex.lex bison.y
	if [ ! -d "bin" ]; then	mkdir bin; fi
	$(MAKE) bison
	@echo "\n***********************************\n"
	$(MAKE) flex
	@echo "\n***********************************\n"
	$(MAKE) compile
	mv a.out bin/a.out

flex:
		flex flex.lex
		mv lex.yy.c bin/lex.yy.c

bison:
		bison -o bin/bison.yy.h bison.y

compile:
	if [ ! -d "bin" ]; then	mkdir bin; fi
	cp commands.h bin/
	cp errors.h bin/
	cp pidentifierAdding.h bin/
	cp constants.h bin/
	cp IO.h bin/
	cp numberCreation.h bin/
	cp assignment.h bin/
	cp arithmetic.h bin/
	cp conditions.h bin/
	cp loops.h bin/
	g++ -std=c++11 -g bin/lex.yy.c bin/bison.yy.h -ll -lm -Wno-write-strings

run:
	$(MAKE) both
	./bin/a.out
