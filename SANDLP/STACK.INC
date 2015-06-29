*	Stack ops.  Functions to implement push down (LIFO) stacks using
*	new defined data types.  An arbitrary number of independent stacks
*	can be created.  Each stack element has a value, V, and a pointer
*	to the previous stack element.  The value may be any SPITBOL or
*	program defined data type.
*
*	This package contains the following operations:
*
*	STACK, PUSH, POP, SWITCH, PRTSTK, SSIZE, SCOPY, and SINIT.
*
*	To create a new stack, use the data type creation function STACK.
*	For example, to create two new stacks, S1 and S2:
*
*		S1	=	STACK()
*		S2	=	STACK()
*
*	To push a value V into stack S, use:
*	
*		PUSH(V, S)
*
*	To pop a value from stack S, use:
*
*		V	=	POP(S)
*
*	The POP function fails if the stack is empty.
*
*	The SWITCH function exchanges the argument value with the top
*	value on the stack.  It fails if the stack is empty:
*
*		V2	=	SWITCH(V1, S)
*
*	PRTSTK outputs the contents of stack S.
*
*	SSIZE counts the number of entries on stack S.
*
*	SCOPY creates a copy of stack S.
*
*	SINIT reinitializes a stack.
*
*	From STRING AND LIST PROCESSING IN SNOBOL4 by Ralph E. Griswold,
*			 by permission of the author.
*	----------------------------------------------------------------
*

*	Stack and Element Definitions:

	DATA("STACK(TOP)")
	DATA("PLATE(VALUE,LAST)")

*	Push Value V into Stack S:
*
	DEFINE('PUSH(V,S)')					:(PUSH_END)

PUSH	TOP(S)	=	PLATE(V,TOP(S))				:(RETURN)
PUSH_END

*	Pop and return top value from stack S.  Fail if empty:
*
	DEFINE('POP(S)')					:(POP_END)

POP	POP	=	DIFFER(TOP(S)) VALUE(TOP(S))		:F(FRETURN)
	TOP(S)	=	LAST(TOP(S))				:(RETURN)
POP_END


*	Interchange specified value with stack top.  Fail if empty:
*
	DEFINE("SWITCH(V,S)")					:(SWITCH_END)

SWITCH	SWITCH	=	DIFFER(TOP(S)) VALUE(TOP(S))		:F(FRETURN)
	VALUE(TOP(S))	=	V				:(RETURN)
SWITCH_END


*	Print contents of stack S:
*
 	DEFINE("PRTSTK(S)P")					:(PRTSTK_END)

PRTSTK	P	=	TOP(S)
PRTS1	OUTPUT	=	DIFFER(P) VALUE(P)			:F(RETURN)
	P	=	LAST(P)					:(PRTS1)
PRTSTK_END


*	Count the number of items on stack S:
*
 	DEFINE("SSIZE(S)")					:(SSIZE_END)

SSIZE	SSIZE	=	0
	S	=	TOP(S)
SSIZEL	SSIZE	=	DIFFER(S) SSIZE + 1			:F(RETURN)
	S	=	LAST(S)					:(SSIZEL)
SSIZE_END


*	Create a unique copy of stack S.  Returns new stack pointer:
*
	DEFINE("SCOPY(S)T")					:(SCOPY_END)

SCOPY	SCOPY	=	COPY(S)
	TOP(SCOPY)	=	DIFFER(TOP(S)) COPY(TOP(S))	:F(RETURN)
	T	=	TOP(SCOPY)
SCOPYL	LAST(T)	=	DIFFER(LAST(T)) COPY(LAST(T))		:F(RETURN)
	T	=	LAST(T)					:(SCOPYL)
SCOPY_END


*	Discard a stack's contents and reinitialize the stack:
*
 	DEFINE("SINIT(S)")					:(SINIT_END)

SINIT	TOP(S)	=						:(RETURN)
SINIT_END
