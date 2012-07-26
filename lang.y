%{
#define YYERROR_VERBOSE 1

#include <glib.h>
#include <stdio.h>
#include "lang.h"
#include "parse.h"
#include "pt-variable.h"

#define YYPARSE_PARAM scanner
#define YYLEX_PARAM   scanner

extern void yyerror(const char *);
/*
 * threw in the gpointer -- flex docs say use yyscan_t, but that doesn't parse.
 */
extern int yylex(YYSTYPE *, YYLTYPE *, gpointer);
extern int yylineno;

static GNode *root = NULL;
GNode *parser_tree_root() { return root; }

%}

%locations
%pure-parser

%union {
   int integer;
   double fp;
   char *string;
   char relop;
   char v_c; /* value-character */
   FILE *file;
   GNode *y_tree;
   gpointer y_alwaysnull;
}
%token <v_c> LBRACKET RBRACKET
%token <v_c> LPAREN RPAREN
%token <v_c> SEPARATOR
%token <v_c> SENTINEL
%token <v_c> DOT
%token <string> SELECT
%token <string> QUIT
%token <string> WHERE
%token <relop> RELOP
%token <string> ID
%token <fp> FLOAT
%token <integer> INTEGER

%type <y_tree> IDList
%type <y_tree> Identifier

%destructor { g_free($$); } SELECT WHERE QUIT ID

%%

Query
  : SELECT IDList {
    root = mk_ptree_node(PT_QUERY, yylineno,0, $2, NULL);
    g_free($1);
  }
  | QUIT {
    root = mk_ptree_node(PT_QUIT, yylineno,0, NULL);
    g_free($1);
  }
  ;

IDList
  : IDList SEPARATOR Identifier {
    g_assert($1 != NULL);
    g_assert($3 != NULL);
    $$ = mk_ptree_node(PT_LIST, yylineno,@1.first_column, $1, $3, NULL);
  }
  | Identifier { $$ = $1; }
  ;

Identifier
  : ID {
    $$ = mk_ptree_node(PT_VARIABLE, yylineno,@1.first_column, NULL);
    g_assert($$->parent == NULL);
    PT_NODE_PTR(ptVariable, $$)->name = g_strdup($1);
  }
