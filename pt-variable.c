#include "pt-variable.h"

static void var_print(const GNode*);
static void var_destroy(GNode*);

G_GNUC_MALLOC ptVariable*
pt_variable_alloc()
{
  ptVariable* v = g_new0(ptVariable, 1);
  v->meta.vtable.print = var_print;
  v->meta.vtable.destroy = var_destroy;

  v->name = NULL;
  return v;
}

static void
var_print(const GNode* gn)
{
  const ptVariable* v = PT_NODE_PTR(const ptVariable, gn);
  g_assert(v->meta.type == PT_VARIABLE);
  g_print("var %s\n", v->name);
}

static void
var_destroy(GNode* gn)
{
  ptVariable* v = PT_NODE_PTR(ptVariable, gn);
  g_assert(v->meta.type == PT_VARIABLE);
  g_free(v->name);
}
