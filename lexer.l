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

%%

{SELECT} { yylval->string = g_strdup("SELECT"); return SELECT; }
{WHERE}  { yylval->string = g_strdup("WHERE"); return WHERE; }
{FLT} { yylval->fp = atof(yytext); return FLOAT; }
"{" { yylval->v_c = '{'; return LBRACKET; }
"}" { yylval->v_c = '}'; return RBRACKET; }
"(" { yylval->v_c = '('; return LPAREN; }
")" { yylval->v_c = ')'; return RPAREN; }
"," { yylval->v_c = ','; return SEPARATOR; }
";" { return SENTINEL; }
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
   yylval->integer = atoi(yytext);
   return INTEGER;
}

[ \t\n]+  /* whitespace is unimportant. */

"." {
   yylval->v_c = '.';
   return DOT;
}
. { printf("unrecognized character: [%s]\n", yytext); }

%%
