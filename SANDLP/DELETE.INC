*	Function to delete all occurrences of a set of characters from a string.
*
*	C is a string containing a list of characters to be deleted from
*	string S.  The function fails if C is null.
*
*	From STRING AND LIST PROCESSING IN SNOBOL4 by Ralph E. Griswold,
*			 by permission of the author.
*	----------------------------------------------------------------
*

	DEFINE("DELETE(S,C)")
	DELPAT	=	POS(0) BREAK(*C) . H SPAN(*C)		:(DELETE_END)

DELETE	IDENT(C)						:S(FRETURN)
DELOOP	S ? DELPAT	=					:F(DELRET)
	DELETE	=	DELETE H				:(DELOOP)
DELRET	DELETE	=	DELETE S				:(RETURN)
DELETE_END
