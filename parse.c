#include <glib.h>
#include "parse.h"

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

static G_GNUC_MALLOC ParseTree*
ptree_alloc(enum PTType type)
{
  ParseTree* retval;
  switch(type) {
    case PT_QUERY:
      retval = (ParseTree*) g_new0(GenericParseTree, 1);
      break;
  }
  return retval;
}
