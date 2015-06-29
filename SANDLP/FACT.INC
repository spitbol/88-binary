*	Factorial.  Here are two versions of the factorial function.  The
*	first is recursive, the second iterative.  Real or integer arguments
*	may be used with either.
*
*	From STRING AND LIST PROCESSING IN SNOBOL4 by Ralph E. Griswold,
*			 by permission of the author.
*	----------------------------------------------------------------
*
*	Recursive factorial function.
	DEFINE("FACT(N)")					:(FACT_END)

FACT	FACT	=	LE(N,1) 1				:S(RETURN)
	FACT	=	N * FACT(N - 1)				:(RETURN)
FACT_END

*	Iterative factorial function.
	DEFINE("FACTI(N)")					:(FACTI_END)

FACTI	FACTI	=	LE(N,1) 1				:S(RETURN)
	FACTI	=	N
FACTI1	N	=	GT(N,2) N - 1				:F(RETURN)
	FACTI	=	FACTI * N				:(FACTI1)
FACTI_END
