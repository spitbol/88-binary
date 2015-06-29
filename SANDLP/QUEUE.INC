*	Queue manipulation routines to maintain a FIFO list of elements.  The
*	list is singly-linked, with a head and tail pointer.  An arbitrary number
*	of independent queues can be created.  Each list element has a value, V,
*	and a pointer to the next list element.  The value may be any SNOBOL4
*	or program defined data type.
*
*	This package contains the following operations:
*
*	QUEUE, APPEND, REMOVE, STKQUE, QUESTK, COPYL, PRTQUE, and QINIT.
*
*	To create a new queue, use the data type creation function QUEUE.
*	For example, to create two new queues, Q1 and Q2:
*
*		Q1	=	QUEUE()
*		Q2	=	QUEUE()
*
*	To add a value V to the end of a queue Q, use:
*	
*		APPEND(V, Q)
*
*	To remove a value from the beginning of queue Q, use:
*
*		V	=	REMOVE(Q)
*
*	The REMOVE function fails if the queue is empty.
*
*	The STKQUE function converts a stack to a queue.
*	See package STACK.SNO for the stack functions.
*
*	The QUESTK function converts a queue to a stack.
*
*	COPYL creates a copy of queue Q.
*
*	PRTQUE prints the contents of a queue.
*
*	QINIT discards a queue's contents and reinitializes the queue.
*
*	From STRING AND LIST PROCESSING IN SNOBOL4 by Ralph E. Griswold,
*			 by permission of the author.
*	----------------------------------------------------------------
*

*	Queue and Element Definitions:

	DATA("QUEUE(HEAD,TAIL)")
	DATA("ELEMENT(VALUE,NEXT)")

*	Add an element to the end of a queue.
*
	DEFINE("APPEND(V,Q)E")					:(APPEND_END)

APPEND	E	=	TAIL(Q)
	TAIL(Q)	=	ELEMENT(V)
	HEAD(Q)	=	IDENT(E) TAIL(Q)			:S(RETURN)
	NEXT(E)	=	TAIL(Q)					:(RETURN)
APPEND_END

*	Remove and return element from beginning of queue.
*
	DEFINE("REMOVE(Q)")					:(REMOVE_END)

REMOVE	REMOVE	=	DIFFER(HEAD(Q)) VALUE(HEAD(Q)) 		:F(FRETURN)
	HEAD(Q)	=	NEXT(HEAD(Q))
	TAIL(Q)	=	IDENT(HEAD(Q))				:(RETURN)
REMOVE_END


*	Convert a stack to a queue.  The LIFO nature of the stack is maintained.
*	The argument Q is returned as the value of the function.
*
*	Call: STKQUE(stack name, queue name)
*
	DEFINE("STKQUE(S,STKQUE)")				:(STKQUE_END)

STKQUE	APPEND(POP(S),STKQUE)					:S(STKQUE)F(RETURN)
STKQUE_END


*	Convert a queue to a stack.  The FIFO nature of the queue is
*	reversed, and becomes LIFO on the stack.  The argument stack is
*	returned as the value of the function.
*
*	Call: QUESTK(queue name, stack name)
*
*	Note that QUESTK(STKQUE(S,Q),S) reverses the order of elements on stack S,
*	and STKQUE(QUESTK(Q,S),Q) reverses the order of elements on queue Q.
*
	DEFINE("QUESTK(Q,QUESTK)")				:(QUESTK_END)

QUESTK	PUSH(REMOVE(Q),QUESTK)					:S(QUESTK)F(RETURN)
QUESTK_END


*	Create a unique copy of a queue.
*
	DEFINE("COPYL(Q)")					:(COPYL_END)

COPYL	COPYL	=	QUEUE()
	E	=	DIFFER(HEAD(Q)) COPY(HEAD(Q))		:F(RETURN)
	HEAD(COPYL)	=	E
COPYLP	NEXT(E)	=	DIFFER(NEXT(E)) COPY(NEXT(E))		:F(COPYL1)
	E	=	NEXT(E)					:(COPYLP)
COPYL1	TAIL(COPYL)	=	E				:(RETURN)
COPYL_END


*	Print contents of queue Q:
*
 	DEFINE("PRTQUE(Q)P")					:(PRTQUE_END)

PRTQUE	P	=	HEAD(Q)
PRTQ1	OUTPUT	=	DIFFER(P) VALUE(P)			:F(RETURN)
	P	=	NEXT(P)					:(PRTQ1)
PRTQUE_END


*	Discard a queue's contents and reinitialize the queue:
*
 	DEFINE("QINIT(Q)")					:(QINIT_END)

QINIT	HEAD(Q)	=
	TAIL(Q)	=						:(RETURN)
QINIT_END
