#ifndef PT_RELATION_H
#define PT_RELATION_H

#include <glib.h>
#include "parse.h"

typedef struct pt_relation_ {
  ParseTree meta;
  char op;
} ptRelation;

G_GNUC_MALLOC G_GNUC_WARN_UNUSED_RESULT ptRelation* pt_relation_alloc();

#endif /* PT_RELATION_H */
