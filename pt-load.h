#ifndef QDV_PT_LOAD_H
#define QDV_PT_LOAD_H

#include "parse.h"

typedef struct parsetree_load_ {
  ParseTree meta;
  char* filename;
} ptLoad;

G_GNUC_MALLOC G_GNUC_WARN_UNUSED_RESULT ptLoad* pt_load_alloc();

#endif /* QDV_PT_LOAD_H */
