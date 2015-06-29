*	CTRIM.  Function to trim an arbitrary set of characters from the
*	end of a string.  Any characters from the string C are removed from
*	the end of the argument string.  If C is omitted, blank is assumed,
*	and the function behaves like the built-in trim function.
*
*	From STRING AND LIST PROCESSING IN SNOBOL4 by Ralph E. Griswold,
*			 by permission of the author.
*	----------------------------------------------------------------
*
	DEFINE("CTRIM(CTRIM,C)")
	CTRIMPAT	=	POS(0) SPAN(*C) REM . CTRIM	:(CTRIM_END)

CTRIM	C	=	IDENT(C) " "
	REVERSE(CTRIM) ? CTRIMPAT				:F(RETURN)
	CTRIM	=	REVERSE(CTRIM)				:(RETURN)
CTRIM_END
