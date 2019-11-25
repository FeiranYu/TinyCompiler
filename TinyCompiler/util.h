#pragma once

#ifndef _UTIL_H_
#define UTIL_H_
#include"globals.h"
/* Procedure printToken prints a token 
* and tis lexeme to the listing file
*/
void printToken(TokenType, const char*);

/* Function newStmtNode creates a new statement
 * node for syntax tree construction 
 */
TreeNode* newStmtNode(StmtKind);

/* Function newExpNode creates a new expression
 * node for syntax tree construction
 */
TreeNode* newExpNode(ExpKind);

/* Funtion copyString allocates and makes a new 
 * copy of an existing string 
 */
char* copyString(char*);

/* procedure printTree prints a syntax tree to the
 * listing file using indentation to indicate subtrees
 */
void printTree(TreeNode);
#endif