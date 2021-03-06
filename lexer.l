%{
#define YY_USE_PROTOS 1
#define _POSIX_C_SOURCE 200112L
#include <glib.h>
#include <stdio.h>
#include "lang.h"

%}

%option bison-bridge bison-locations
%option yylineno

FLT        "-"?([[:digit:]]+\.[[:digit:]]+)
IDENTIFIER ([[:alpha:]])+([[:alnum]])*
INT        ([[:digit:]])+
SELECT     ([Ss][Ee][Ll][Ee][Cc][Tt])
WHERE      ([Ww][Hh][Ee][Rr][Ee])
QUIT       ([Qq][Uu][Ii][Tt])
AND        ([Aa][Nn][Dd])
LOAD       ([Ll][Oo][Aa][Dd])
PATH       ([[:alnum:]]*[[:punct:]]*[[:alnum:]]*)+

%%

{LOAD}   { yylval->string = g_strdup("LOAD"); return LOAD; }
{SELECT} { yylval->string = g_strdup("SELECT"); return SELECT; }
{WHERE}  { yylval->string = g_strdup("WHERE"); return WHERE; }
{QUIT}   { yylval->string = g_strdup("QUIT"); return QUIT; }
{AND}   { yylval->string = g_strdup("AND"); return AND; }
{FLT} { yylval->fp = atof(yytext); return FLOAT; }
"{" { yylval->v_c = '{'; return LBRACKET; }
"}" { yylval->v_c = '}'; return RBRACKET; }
"(" { yylval->v_c = '('; return LPAREN; }
")" { yylval->v_c = ')'; return RPAREN; }
"," { yylval->v_c = ','; return SEPARATOR; }
";" { yylval->v_c = ';'; return SENTINEL; }
"<" { yylval->relop = '<'; return RELOP; }
">" { yylval->relop = '>'; return RELOP; }
"<=" { yylval->relop = 'l'; return RELOP; }
">=" { yylval->relop = 'g'; return RELOP; }
"==" { yylval->relop = '='; return RELOP; }
"!=" { yylval->relop = '!'; return RELOP; }
{IDENTIFIER} {
   yylval->string = g_strdup(yytext);
   return ID;
}
{INT} {
   yylval->integer = atoll(yytext);
   return INTEGER;
}

[ \t\n]+  /* whitespace is unimportant. */

"." {
   yylval->v_c = '.';
   return DOT;
}
{PATH}  { yylval->string = g_strdup(yytext); return PATH; }
. { printf("unrecognized character: [%s]\n", yytext); }

%%
