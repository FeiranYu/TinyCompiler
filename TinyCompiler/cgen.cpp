#include"globals.h"
#include"symtab.h"
#include"code.h"
#include"cgen.h"

/* tmpOffset is the memory offset for temps
	It is decremented each time a temp is
	stored, and incremented when loaded again
*/
static int tmpOffset = 0;

/* prototype for internal recursive code generator */
static void cGen(TreeNode* tree);

/* Procedure genStmt generates code at a statement node */
static void genStmt(TreeNode* tree)
{
	TreeNode* p1, * p2, * p3;
	int savedLoc1, savedLoc2, currentLoc;
	int loc;
	switch (tree->kind.stmt)
	{
	case IfK:
		if (TraceCode)emitComment("-> if");
		p1 = tree->child[0];
		p2 = tree->child[1];
		p3 = tree->child[2];
		/* generate code for test expression */
		cGen(p1);
		savedLoc1 = emitSkip(1);
		emitComment("if: jump to else belongs here");
		/* recurse on then part */
		cGen(p2);
		savedLoc2 = emitSkip(1);
		emitComment("if: jump to end belongs here");
		currentLoc = emitSkip(0);
		emitBackup(savedLoc1);
		emitRM_Abs("JEQ", ac, currentLoc, "if: jmp to end");
		emitRestore();
		/* recurse on else part */
		cGen(p3);
		currentLoc = emitSkip(0);
		emitBackup(savedLoc2);
		emitRM_Abs("LDA", pc, currentLoc, "jmp to end");
		emitRestore();
		if (TraceCode) emitComment("<- if");
		break; /* if_k */
	case RepeatK:
		if (TraceCode)emitComment("-> repeat");
		p1 = tree->child[0];
		p2 = tree->child[1];
		savedLoc1 = emitSkip(0);
		emitComment("repeat: jump after body comes back here ");
		/* generate code for body */
		cGen(p1);
		/* generate code for test */
		cGen(p2);
		emitRM_Abs("JEQ", ac, savedLoc1, "repeat: jmp back to body");
		if (TraceCode) emitComment("<- repeat");
		break; /* repeat */
	case AssignK:
		if (TraceCode) emitComment("-> assign");
		/* generate code for rhs */
		cGen(tree->child[0]);
		/* now store value */
		loc = st_lookup(tree->attr.name);
		emitRM("ST", ac, loc, gp, "assign: store value");
		if (TraceCode)emitComment("<- assign");
		break; /* assign_k */
	case ReadK:
		emitRO("IN", ac, 0, 0, "read integer value");
		loc = st_lookup(tree->attr.name);
		emitRM("ST", ac, loc, gp, "read: store value");
		break;
	case WriteK:
		/* generate code for expression to write */
		cGen(tree->child[0]);
		/* now output it */
		emitRO("OUT", ac, 0, 0, "write ac");
		break;
	default:
		break;
		
	}
} /* genStmt */

