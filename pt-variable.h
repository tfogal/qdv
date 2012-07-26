#ifndef PT_VARIABLE_H
#define PT_VARIABLE_H

#include <glib.h>
#include "parse.h"

typedef struct pt_variable_ {
  ParseTree meta;
  char* name;
} ptVariable;

G_GNUC_MALLOC ptVariable* pt_variable_alloc();

#endif /* PT_VARIABLE_H */
