#ifndef QDV_PARSE_H
#define QDV_PARSE_H

#include <glib.h>

enum PTType {
  PT_QUERY
};

typedef struct _ptree_vtable {
} ptree_vtable;

/* `base' type.  All trees have a `tree' named `meta' as their first field, so
 * the beginning of a tree has a constant layout in memory. */
typedef struct _ptree {
  ptree_vtable vtable;
  enum PTType type;
  /* error reporting: */
  size_t line_no;
  size_t col_no;
} ParseTree;

/** abstract, generic tree.  essentially a copy of Tree, but this makes casting
 * appear safe. */
typedef struct _abs_ptree {
  ParseTree meta;
} GenericParseTree ;

/** Accepts a node type, the line number and column it came from, and a list of
 * of GNode*'s which should be its children.  The list MUST be NULL-terminated,
 * even if it is empty. */
G_GNUC_WARN_UNUSED_RESULT G_GNUC_NULL_TERMINATED G_GNUC_MALLOC GNode *
mk_ptree_node(enum PTType, gsize line, gsize column, ...);

#endif /* QDV_PARSE_H */
