/** A generic value: string, integer, or floating point number. */
#ifndef QDV_GN_VALUE_H
#define QDV_GN_VALUE_H

#include <stdio.h>

enum GNValueType {
   GNV_STRING, GNV_INTEGER, GNV_FLOAT
};

/* Represents an abstract `value'.  It is essentially untyped because we can't
 * assume anything about the type, really.  This is the thing that will come
 * (e.g.) to the right of an equals sign:
 *      abc.xyz = "blah"
 * or:
 *      abc.abc = 42
 */
typedef union _abs_value {
   char* string;
   gint integer;
   gfloat fp;
} AbstractValue;

typedef struct _gn_value {
   union {
      char* string;
      gint integer;
      gfloat fp;
   };
   enum GNValueType type;
} Value;

static inline void value_print(const Value val)
{
   switch(val.type) {
      case GNV_FLOAT:   printf("%f", val.fp); break;
      case GNV_INTEGER: printf("%d", val.integer); break;
      case GNV_STRING:  printf("%s", val.string); break;
   }
}
static inline G_GNUC_MALLOC gchar* value_as_string(const Value val)
{
   switch(val.type) {
      case GNV_FLOAT:   return g_strdup_printf("%f", val.fp); break;
      case GNV_INTEGER: return g_strdup_printf("%d", val.integer); break;
      case GNV_STRING:  return g_strdup_printf("%s", val.string); break;
   }
   return NULL;
}

static inline void value_setf(Value* val, const float f)
{
   val->fp = f;
   val->type = GNV_FLOAT;
}

static inline void value_seti(Value* val, const int i)
{
   val->integer = i;
   val->type = GNV_INTEGER;
}

static inline void value_sets(Value* val, const char* s)
{
   val->string = g_strdup(s);
   val->type = GNV_STRING;
}

static inline void value_destroy(Value* val)
{
   if(val->type == GNV_STRING) {
      g_free(val->string);
   }
}

#endif /* QDV_GN_VALUE_H */
