CFLAGS=-std=c99 -Wall -Wextra $(shell pkg-config --cflags glib-2.0) -g
OBJ=qdv.o lang.o lexer.o parse.o pt-variable.o
LDFLAGS=$(shell pkg-config --libs glib-2.0) -lreadline -lfl
LEX=flex
YACC=bison
YFLAGS=-d

all: $(OBJ) query

query: qdv.o lang.o lexer.o parse.o pt-variable.o
	$(CC) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(OBJ) query

%.c: %.l
	$(LEX) -o $@ $^
%.c: %.y
	$(YACC) $(YFLAGS) -o $@ $^
lang.h: lang.y
	$(YACC) $(YFLAGS) -o $@ $^
