#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

struct yy_buf_state;
typedef struct yy_buf_state* YY_BUFFER_STATE;
extern void yy_delete_buffer(YY_BUFFER_STATE);
extern YY_BUFFER_STATE yy_scan_string(const char*);
extern void yyparse(void);

void
yyerror(const char *s)
{
   fprintf(stderr, "%s\n", s);
}

int main() {
  char* cmd;
  do {
    cmd = readline("> ");
    if(cmd) {
      printf("processing: '%s'\n", cmd);
      YY_BUFFER_STATE st = yy_scan_string(cmd);
      yyparse();
      yy_delete_buffer(st);
    }
  } while(cmd != NULL);
  puts("");
  return EXIT_SUCCESS;
}
