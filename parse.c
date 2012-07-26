#include <stdio.h>
#include <glib.h>
#include "parse.h"
#include "pt-variable.h"

static G_GNUC_MALLOC ParseTree* ptree_alloc(enum PTType type);

/** Accepts a node type, the line number and column it came from, and a list of
 * of GNode*'s which should be its children.  The list MUST be NULL-terminated,
 * even if it is empty. */
G_GNUC_WARN_UNUSED_RESULT G_GNUC_NULL_TERMINATED G_GNUC_MALLOC GNode*
mk_ptree_node(enum PTType type, gsize line, gsize column, ...)
{
   va_list ap;
   GenericParseTree *gt;
   GNode *head, *add;

   gt = (GenericParseTree *) ptree_alloc(type);
   gt->meta.type = type;
   gt->meta.line_no = line;
   gt->meta.col_no = column;

   head = g_node_new(gt);

   va_start(ap, column);
      while((add = va_arg(ap, GNode*)) != NULL) {
         g_node_append(head, add);
      }
   va_end(ap);

   return head;
}

/* a generic parse-tree print function, that only assumes it is getting a parse
 * tree node. */
static void
pr_unknown(const GNode *gn)
{
  const ParseTree tdata = PT_META(gn);
  switch(tdata.type) {
    case PT_QUERY: g_print("query"); break;
    case PT_QUIT: g_print("quit"); break;
    default: g_print("(unknown type)"); break;
  }
#ifdef _LP64
  g_print(" at line %lu, column %lu\n", tdata.line_no, tdata.col_no);
#else
  g_print(" at line %u, column %u\n", tdata.line_no, tdata.col_no);
#endif
}

static G_GNUC_MALLOC ParseTree*
ptree_alloc(enum PTType type)
{
  ParseTree* retval = NULL;
  switch(type) {
    case PT_LIST: /* special case. */
      retval = (ParseTree*) g_new0(GenericParseTree, 1);
      retval->vtable.print = pr_unknown;
      break;
    case PT_QUERY: /* special case */
      retval = (ParseTree*) g_new0(GenericParseTree, 1);
      retval->vtable.print = pr_unknown;
      break;
    case PT_QUIT: /* special case. */
      retval = (ParseTree*) g_new0(GenericParseTree, 1);
      retval->vtable.print = pr_unknown;
      break;
    case PT_VARIABLE:
      retval = (ParseTree*) pt_variable_alloc();
      break;
  }
  g_assert(retval != NULL && "forgot to add alloc case?");
  return retval;
}

static const int VISIT_ALL_NODES = -1;
static const gboolean CONTINUE_TRAVERSAL = FALSE;
static const gboolean STOP_TRAVERSAL = TRUE;

static gboolean
destroy_(GNode* node, G_GNUC_UNUSED gpointer udata)
{
  if(PT_META(node).vtable.destroy) {
    PT_META(node).vtable.destroy(node);
  }
  g_free(node->data);
  return CONTINUE_TRAVERSAL;
}
/** Calls the destructor on every element of the tree. */
void
destroy(GNode* root)
{
  g_node_traverse(root, G_POST_ORDER, G_TRAVERSE_ALL, -1, destroy_, NULL);
}

static gboolean
print_(GNode* node, G_GNUC_UNUSED gpointer udata)
{
  if(PT_META(node).vtable.print) {
    PT_META(node).vtable.print(node);
  }
  return CONTINUE_TRAVERSAL;
}

void
pt_print(GNode* root)
{
  g_node_traverse(root, G_PRE_ORDER, G_TRAVERSE_LEAVES, VISIT_ALL_NODES,
                  print_, stdout);
  g_print("\n");
}
