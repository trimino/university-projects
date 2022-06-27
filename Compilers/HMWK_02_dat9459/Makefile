# David Trimino
# dat9459
# 2021-03-08

PROJS  = myLexer
CC     = gcc
CFLAGS = -g -Wall -Wextra -fsanitize=address -fsanitize=leak -static-libasan

all : $(PROJS)

myLexer : myLexer.l
	flex myLexer.l
	$(CC) $(CFLAGS) -o myLexer lex.yy.c

clean:
	rm -f *.o $(PROJS) lex.yy.[ch] minimal?.tab.[ch]
