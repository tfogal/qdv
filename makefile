GLIB_CF=$(shell pkg-config --cflags glib-2.0)
CFLAGS=-std=c99 $(GLIB_CF) -Wall -Wextra -Werror -g
OBJ=constant.o qdv.o lang.o lexer.o parse.o \
  pt-load.o pt-relation.o pt-variable.o pt-variable-ref.o
LDFLAGS=$(shell pkg-config --libs glib-2.0) -lreadline -lfl
LEX=flex
YACC=bison
YFLAGS=-d

all: $(OBJ) query

query: constant.o qdv.o lang.o lexer.o parse.o \
  pt-load.o pt-relation.o pt-variable.o pt-variable-ref.o
	$(CC) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(OBJ) query

%.c: %.l
	$(LEX) -o $@ $^
%.c: %.y
	$(YACC) $(YFLAGS) -o $@ $^
lang.h: lang.y
	$(YACC) $(YFLAGS) -o $@ $^

# stupid flex/bison produces warnings.
lexer.o: lexer.c
	$(CC) -c -std=c99 -Wno-implicit-function-declaration $(GLIB_CF) $^ -o $@
