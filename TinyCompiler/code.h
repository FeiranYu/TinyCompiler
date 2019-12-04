#pragma once
#ifndef _CODE_H_
#define _CODE_H_

/* PC = PROGRAM COUNTER */
#define pc 7

/* mp = "memory pointer" points
 * to top of memory (for temp storage)
 */
#define mp 6

/* gp = "global pointer" points
 * to bottom of memory for (global)
 * variable storage
 */
#define gp 5

/* accumulator */
#define ac 0

/* accumulator1 */
#define ac1 1
/* code emitting utilities */

/* Procedure emitRO emits a register-only
 * TM instruction
 * op = the opcode
 * r = target register
 * s = 1st source register
 * c = a comment to be printed if TraceCode is True
 */
void emitRO(char* op, int r, int s, int t, char* c);

/* Procedure emitRM emits a register-to-memory
 * TM instruction
 * op = the opcode
 * r = target register
 * d = the offset
 * s = the base register
 * c = a comment to be printed if TraceCode is TRUE
 */
void emitRM(char* op, int r, int d, int s, char* c);

/* Function emitSkip skips "howMany" code
 * locations for later backpatch. It also
 * returns the current code position
 */
int emitSkip(int howMany);

/* Procedure emitBackup backs up to
 * loc = a previously skipped location
 */
void emitBackup(int loc);

