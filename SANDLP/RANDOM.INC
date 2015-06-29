*	Function to generate a random integer in the range 0 to N-1, where
*	N is the argument to the function RANDOM.  RANVAR is the seed for
*	the generator.  If not explicitly set by the user, it begins at 0.
*
*	From STRING AND LIST PROCESSING IN SNOBOL4 by Ralph E. Griswold,
*			 by permission of the author.
*	----------------------------------------------------------------
*
	DEFINE("RANDOM(N)")					:(RANDOM_END)

RANDOM	RANVAR	=	REMDR(RANVAR * 12621 + 21131, 100000)
	RANDOM	=	RANVAR * N / 100000			:(RETURN)
RANDOM_END


*	Function to generate a random character from the full 256 character
*	alphabet.
*
	DEFINE("RANCHR()")
	ASIZE	=	SIZE(&ALPHABET)
	RANSEL	=	TAB(*RANDOM(ASIZE)) LEN(1) . RANCHR	:(RANCHR_END)

RANCHR	&ALPHABET ? RANSEL					:(RETURN)
RANCHR_END
