#include "pt-variable-ref.h"

static void vref_print(const GNode*);
static void vref_destroy(GNode*);

G_GNUC_MALLOC ptVRef*
pt_vref_alloc()
{
  ptVRef* v = g_new0(ptVRef, 1);
  v->meta.vtable.print = vref_print;
  v->meta.vtable.destroy = vref_destroy;
  return v;
}

static void
vref_print(const GNode* node)
{
  const ptVRef* vref = PT_NODE_PTR(const ptVRef, node);
  g_assert(vref->meta.type == PT_VARIABLE_REFERENCE);
  g_print("vref %s\n", vref->name);
}

static void
vref_destroy(GNode* gn)
{
  ptVRef* vref = PT_NODE_PTR(ptVRef, gn);
  g_assert(vref->meta.type == PT_VARIABLE_REFERENCE);
  g_free(vref->name);
}
