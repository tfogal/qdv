#include "pt-relation.h"

static void rel_print(const GNode*);
static void rel_destroy(GNode*);

G_GNUC_MALLOC G_GNUC_WARN_UNUSED_RESULT ptRelation*
pt_relation_alloc()
{
  ptRelation* r = g_new0(ptRelation, 1);
  r->meta.vtable.print = rel_print;
  r->meta.vtable.destroy = rel_destroy;
  return r;
}

static void
rel_print(const GNode* gn)
{
  const ptRelation* rel = PT_NODE_PTR(const ptRelation, gn);
  g_assert(rel->meta.type == PT_RELATION);
  g_print("relational op: '%c'\n", rel->op);
}

static void
rel_destroy(GNode* gn)
{
  g_assert(PT_NODE_TYPE(gn) == PT_RELATION);
}
