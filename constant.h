#ifndef QDV_CONSTANT_H
#define QDV_CONSTANT_H
/** 'Constant' node in a tree: holds a constant value given by the user. */

#include <glib.h>
#include "parse.h"
#include "value.h"

typedef struct constant_ {
  ParseTree meta;
  Value value;
} Constant;

G_GNUC_MALLOC Constant* pt_constant_alloc();

/** Makes this constant a constant string.  The string is copied. */
static inline void constant_sets(Constant* c, const gchar* s)
{
   value_sets(&(c->value), s);
}

/** Makes this constant a constant integer. */
static inline void constant_seti(Constant* c, gint i)
{
   value_seti(&(c->value), i);
}

/** Makes this constant a constant integer. */
static inline void constant_setf(Constant* c, gdouble f)
{
   value_setf(&(c->value), f);
}

#endif /* QDV_CONSTANT_H */
