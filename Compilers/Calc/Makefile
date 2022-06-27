# David Trimino
# dat9459
# 2020-04-06

FILES  = lex.yy.c parser.tab.c expr.c main.c
CC     = gcc
CFLAGS = -g -Wall -Wextra -fsanitize=address -fsanitize=leak -static-libasan

calc : $(FILES)
	$(CC) $(CFLAGS) $(FILES) -o calc

lex.yy.c : lexer.l
	flex lexer.l

parser.tab.c : parser.y lex.yy.c
	bison --report=all --xml parser.y
	xsltproc /usr/share/bison/xslt/xml2xhtml.xsl parser.xml > parser.html
	rm -f parser.xml

clean:
	rm -f *.o lex.yy.c lex.yy.h parser.tab.c parser.tab.h parser.output parser.xml parser.html calc
