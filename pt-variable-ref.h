#ifndef PT_VARIABLE_REF_H
#define PT_VARIABLE_REF_H

#include <glib.h>
#include "parse.h"

typedef struct pt_variable_ref_ {
  ParseTree meta;
  char* name;
} ptVRef;

G_GNUC_MALLOC ptVRef* pt_vref_alloc();

#endif /* PT_VARIABLE_REF_H */
