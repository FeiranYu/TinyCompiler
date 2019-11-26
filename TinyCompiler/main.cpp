#include"globals.h"

/* set NO_PARSE to TRUE to get a scanner-only compiler */
#define NO_PARSE FALSE

/* set NO_ANALYZE to TRUE to get a parser-only complier */
#define NO_ANALYZE TRUE

/* set NO_CODE to TRUE to get a compiler that does not generate code */
#define NO_CODE FALSE

#include"util.h"
#if NO_PARSE
#include "scan.h"
#else 
#include"parse.h"

#endif

/* allocate global variable */
int lineno = 0;
FILE* source;
FILE* listing;
FILE* code;

/* allocate and set tracing flags */
int EchoSource = TRUE;
int TraceScan = TRUE;
int TraceParse = TRUE;
int TraceAnalyze = TRUE;
int TraceCode = TRUE;

int Error = FALSE;

int main(int argc, char* argv[])
{
	TreeNode* syntaxTree;
	char pgm[20];	/*source code file name */
	/*
	if (argc != 2)
	{
		fprintf(stderr, "usage: %s <filename>\n", argv[0]);
		exit(1);
	}
	strcpy(pgm, argv[1]);
	if (strchr(pgm, '.') == NULL)
		strcat(pgm, ".tny");
	*/
	strcpy(pgm, "sample.tny");
	source = fopen(pgm, "r");
	if (source == NULL)
	{
		fprintf(stderr, "File %s not found\n", pgm);
		exit(1);
	}
	listing = stdout;	/*send listing to screen */
#if NO_PARSE
	while (getToken() != ENDFILE);
#endif
	syntaxTree = parse();
	if(TraceParse) {
		fprintf(listing, "\nSyntax tree:\n");
		printTree(syntaxTree);
	}
	return 0;
}