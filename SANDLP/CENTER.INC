*	Function to center a string S in width N, using fill character C.
*
*	If S cannot be precisely centered, it is placed one character to
*	the left of center.  If C is omitted, blank is assumed.  The function
*	fails if N is less than the length of string S.
*
*	From STRING AND LIST PROCESSING IN SNOBOL4 by Ralph E. Griswold,
*			 by permission of the author.
*	----------------------------------------------------------------
*

	DEFINE("CENTER(S,N,C)M,H")
	FILLPAT	=	LEN(1) . C				:(CENTER_END)

CENTER	C ? FILLPAT						:S(CENTRR)
	C	=	" "
CENTRR	M	=	SIZE(S)
	H	=	GE(N,M) (N - M) / 2			:F(FRETURN)
	M	=	REMDR(N - M,2)
	CENTER	=	DUPL(C,H) S DUPL(C,H + M)		:(RETURN)
CENTER_END
