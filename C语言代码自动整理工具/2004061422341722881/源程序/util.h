#ifndef _UTIL_H_
#define _UTIL_H_

/* procedure printToken prints a token 
 * and its lexeme to the listing file
 */
void printType(Type type);
void printToken(TokenType, const char *);

/* function newNode creates a new treenode
 * for syntax tree construction
 */
TreeNode * newDecNode(DecKind);
TreeNode * newStmtNode(StmtKind);
TreeNode * newExpNode(ExpKind);

/* function copyString allocates and makes a new
 * copy of an existing string
 */
char * copyString(char *);

/* procedure printTree prints a syntax tree to the 
 * listing file using indentation to indicate subtrees
 */
void printTree(TreeNode *);

#endif
