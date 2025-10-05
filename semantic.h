/* semantic.h - simple semantic/type checking for Mini language */

#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ast.h"

/* Type codes */
#define TYPE_INT 0
#define TYPE_STRING 1
#define TYPE_ARRAY_INT 2

/* Perform semantic checks on the AST. Returns 0 on success, non-zero on error. */
int semanticCheck(ASTNode* root);

/* Compute the type of an expression (exposed so later stages can query types).
 * Returns TYPE_INT, TYPE_STRING, TYPE_ARRAY_INT, or -1 on error. Caller should
 * run semanticCheck(root) first so declarations are registered in the symtab.
 */
int exprType(ASTNode* node);

#endif
