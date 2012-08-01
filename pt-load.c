#include "pt-load.h"

static void ld_print(const GNode*);
static void ld_destroy(GNode*);

G_GNUC_MALLOC G_GNUC_WARN_UNUSED_RESULT ptLoad*
pt_load_alloc()
{
  ptLoad* load = g_new0(ptLoad, 1);
  load->meta.vtable.print = ld_print;
  load->meta.vtable.destroy = ld_destroy;
  load->filename = NULL;
  return load;
}

static void
ld_print(const GNode* gn)
{
  g_assert(PT_NODE_TYPE(gn) == PT_LOAD);
  const ptLoad* load = PT_NODE_PTR(const ptLoad, gn);
  g_print("load data set: '%s'\n", load->filename);
}
static void
ld_destroy(GNode* gn)
{
  g_assert(PT_NODE_TYPE(gn) == PT_LOAD);
  const ptLoad* load = PT_NODE_PTR(const ptLoad, gn);
  g_free(load->filename);
}
