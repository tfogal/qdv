%{
#define YYERROR_VERBOSE 1

#include <glib.h>
#include <stdio.h>
#include "lang.h"
#include "parse.h"

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
%token <string> PATH
%token <string> SELECT
%token <string> WHERE
%token <relop> RELOP
%token <string> ID
%token <fp> FLOAT
%token <integer> INTEGER

%%

Query
  : SELECT
  {
    root = mk_ptree_node(PT_QUERY, yylineno,0, NULL);
  }
  ;
