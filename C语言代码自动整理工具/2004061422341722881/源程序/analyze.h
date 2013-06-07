/****************************************************/
/* File: analyze.h                                  */
/* Semantic analyzer interface						*/
/* for the C_Minus compiler                         */
/****************************************************/

#ifndef _ANALYZE_H_
#define _ANALYZE_H_

/* function buildSymtab constructs the symbol 
 * table by preorder traversal of the syntax tree
 */
void buildSymtab(TreeNode *);

/* procedure typeCheck performs type checking 
 * by a postorder syntax tree traversal
 */
void typeCheck(TreeNode *);

#endif