*	Fibonacci.  Here are two versions of the Fibonacci function.  The
*	first is recursive, the second iterative.  Integer arguments
*	are used.
*
*	From STRING AND LIST PROCESSING IN SNOBOL4 by Ralph E. Griswold,
*			 by permission of the author.
*	----------------------------------------------------------------
*
*	Recursive Fibonacci function.
	DEFINE("FIBON(N)")					:(FIBON_END)

FIBON	LT(N,1)							:S(FRETURN)
	FIBON	=	LE(N,2) 1				:S(RETURN)
	FIBON	=	FIBON(N - 1) + FIBON(N - 2)		:(RETURN)
FIBON_END

*	Iterative Fibonacci function.
	DEFINE("FIBONI(N)F1,F2,F3")   				:(FIBONI_END)

FIBONI	F1  =  1;	F2   =	1;	F3  =  0
F1	FIBONI	=	F2 + F3
	F2	=	F3;	F3	=	FIBONI
	F1	=	LT(F1,N) F1 + 1				:S(F1)F(RETURN)
FIBONI_END
