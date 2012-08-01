#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <readline/readline.h>
#include "parse.h"

/* garbage to make flex/bison work. */
struct yy_buf_state;
typedef struct yy_buf_state* YY_BUFFER_STATE;
extern void yy_delete_buffer(YY_BUFFER_STATE);
extern YY_BUFFER_STATE yy_scan_string(const char*);
extern int yyparse(void);
extern int yylex_destroy(void);

extern GNode *parser_tree_root();

void
yyerror(const char *s)
{
   fprintf(stderr, "%s\n", s);
}

bool process(const char* cmd);

int main() {
  char* cmd;
  bool keep_going = true;
  do {
    cmd = readline("> ");
    if(cmd) {
      keep_going = process(cmd);
    }
    free(cmd);
  } while(cmd != NULL && keep_going);
  puts("");
  return EXIT_SUCCESS;
}

bool
process(const char* cmd)
{
  bool continu = true;
  printf("processing: '%s'\n", cmd);

  YY_BUFFER_STATE st = yy_scan_string(cmd);
    int parse_ok = yyparse();
    GNode* parsetree = parser_tree_root();
    if(parse_ok == 0) {
      /* special case: the command is a 'quit' command. */
      if(PT_NODE_TYPE(parsetree) == PT_QUIT) {
        g_print("bye.\n");
        continu = false;
        goto done;
      } else {
        /* for now, just print it for debugging. */
        pt_print(parsetree);
      }
    }

done:
  yy_delete_buffer(st);
  g_debug("destroying tree...");
  if(parsetree && parse_ok == 0) {
    destroy(parsetree);
  }

  yylex_destroy();

  return continu;
}
