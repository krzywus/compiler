
both: flex.lex bison.y
	$(MAKE) bison
	@echo "\n***********************************\n"
	$(MAKE) flex
	@echo "\n***********************************\n"
	$(MAKE) compile
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

compile:
	cp errors.h bin/
	cp sectionsKeywords.h bin/
	cp pidentifierAdding.h bin/
	cp constants.h bin/
	cp IO.h bin/
	cp numberCreation.h bin/
	cp stringStack.h bin/
	cp assignment.h bin/
	gcc -g bin/lex.yy.c bin/bison.yy.h -ll -lm

run:
	$(MAKE) bison
	@echo "\n***********************************\n"
	$(MAKE) flex
	@echo "\n***********************************\n"
	$(MAKE) compile
	mv a.out bin/a.out
	./bin/a.out
