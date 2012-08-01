#include "constant.h"

static void constant_print(const GNode*);
static void constant_destroy(GNode*);

G_GNUC_MALLOC Constant*
pt_constant_alloc()
{
  Constant* c = g_new0(Constant, 1);
  c->meta.vtable.print = constant_print;
  c->meta.vtable.destroy = constant_destroy;
  return c;
}

static void
constant_print(const GNode* gn)
{
  const Constant *c = PT_NODE_PTR(const Constant, gn);
  switch(c->value.type) {
    case GNV_FLOAT:   puts("float constant"); break;
    case GNV_INTEGER: puts("integer constant"); break;
    case GNV_STRING:  puts("string constant"); break;
  }
}

static void
constant_destroy(GNode* gn)
{
  Constant *c = PT_NODE_PTR(Constant, gn);
  value_destroy(&(c->value));
}
