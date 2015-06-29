*	This is the inverse of the COLLATE function.
*	Returns a string comprised of the characters from either the odd or
*	 even character postitions of the argument string.  The argument N
*	  is 0 or 1 to specify returning the even or odd characters.
*
*	Calls function COLLATE.
*
*	From STRING AND LIST PROCESSING IN SNOBOL4 by Ralph E. Griswold,
*			 by permission of the author.
*	----------------------------------------------------------------
*
	DEFINE('DECOLLATE(S,N)S1,S2')
*
*	Create alphabet with a each character doubled:
	DALPHABET	=	COLLATE(&ALPHABET,&ALPHABET)
*
*	Define some patterns for use later:
	DP1	=	LEN(*N) LEN(*SIZE(S)) . S1
	DP2	=	LEN(*((SIZE(S) + N) / 2)) . S2
	DP3	=	LEN(510) . S1				:(DECOLLATE_END)

DECOLLATE
	DALPHABET ? DP1						:F(DECOVR)
	&ALPHABET ? DP2
	DECOLLATE	=	REPLACE(S2,S1,S)		:(RETURN)

*	Here if Size(S)+N is greater than 512 characters.  Use recursion.
DECOVR	S ? DP3	=
	DECOLLATE	=	DECOLLATE(S1,N) DECOLLATE(S,N)	:(RETURN)

DECOLLATE_END
