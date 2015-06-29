*	Function to replace a span of character C in string S with
*	a single use of the character.
*
*	From STRING AND LIST PROCESSING IN SNOBOL4 by Ralph E. Griswold,
*			 by permission of the author.
*	----------------------------------------------------------------
*

	DEFINE("COMPRESS(S,C)H")
	COMPAT	=	POS(0) BREAK(*C) . H SPAN(*C)	:(COMPRESS_END)

COMPRESS S ? COMPAT	=				:F(COMRET)
	COMPRESS	=	COMPRESS H C		:(COMPRESS)
COMRET	COMPRESS	=	COMPRESS S		:(RETURN)
COMPRESS_END
