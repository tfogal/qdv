#ifndef QDV_PARSE_H
#define QDV_PARSE_H
/** Types and functions for building the parse tree ("pt"). */

#include <glib.h>

enum PTType {
  PT_QUERY,
  PT_CONSTANT,
  PT_LOAD,
  PT_LIST,
  PT_QUIT,
  PT_RELATION,
  PT_VARIABLE,
  PT_VARIABLE_REFERENCE,
};

/** The argument must be a GNode from the parse tree.
 * A pt_print function prints out the information about the current tree node,
 * mostly for debugging purposes. */
typedef void (pt_func_print)(const GNode *);

/** Destructor. */
typedef void (pt_func_destroy)(GNode *);

typedef struct _ptree_vtable {
  pt_func_print* print;
  pt_func_destroy* destroy;
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
} GenericParseTree;

/** Accepts a node type, the line number and column it came from, and a list of
 * of GNode*'s which should be its children.  The list MUST be NULL-terminated,
 * even if it is empty. */
G_GNUC_WARN_UNUSED_RESULT G_GNUC_NULL_TERMINATED G_GNUC_MALLOC GNode *
mk_ptree_node(enum PTType, gsize line, gsize column, ...);

#define PT_NODE_PTR(_type, _the_gnode)     \
   ({                                      \
      g_assert(_the_gnode != NULL);        \
      g_assert(_the_gnode->data != NULL);  \
      ((_type*)(_the_gnode->data));        \
   })
#define PT_META(_gnode) (((GenericParseTree*)(_gnode->data))->meta)
#define PT_NODE_TYPE(_gnode) PT_META(_gnode).type

/** Calls the destructor on every element of the tree. */
void destroy(GNode*);

/** Prints out a representation of the tree, for debugging. */
void pt_print(GNode*);

#endif /* QDV_PARSE_H */
