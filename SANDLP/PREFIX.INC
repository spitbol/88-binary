*	These two functions convert arithmetic expressions back and forth
*	between prefix and infix notation.  No operator precedence is assumed:
*	the expressions must be fully parenthesised.  Infix notation is easier
*	for humans to read, prefix notation is easier for computers to process.
*
*	An example of infix and prefix forms is:
*
*	Infix:	((7+X)-(Y*(N+3)))/2
*	Prefix:	/(-(+(7,X),*(Y,+(N,3))),2)
*
*	These functions handle binary operators only; unary operators
*	require a little more work.
*
*	From STRING AND LIST PROCESSING IN SNOBOL4 by Ralph E. Griswold,
*			 by permission of the author.
*	----------------------------------------------------------------
*
	DEFINE("PREFIX(PREFIX)L,R,OP")
	STRIP	=	POS(0) "(" BAL . PREFIX ")" RPOS(0)
	INFIX	=	POS(0) BAL . L ANY("+-*/") . OP
+			BAL . R RPOS(0)				:(PREFIX_END)

PREFIX	PREFIX ? STRIP						:S(PREFIX)
	PREFIX ? INFIX	=   OP "(" PREFIX(L) "," PREFIX(R) ")"	:(RETURN)
PREFIX_END

	DEFINE("INFIX(INFIX)L,R,OP")
	PREFIX	=	POS(0) LEN(1) . OP "(" BAL . L ","
+			BAL . R ")" RPOS(0)			:(INFIX_END)

INFIX	INFIX ? PREFIX	=	"(" INFIX(L) OP INFIX(R) ")"	:(RETURN)
INFIX_END
