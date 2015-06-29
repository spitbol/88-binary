*	Functions to truncate or extend a one dimensional array.
*
*	From STRING AND LIST PROCESSING IN SNOBOL4 by Ralph E. Griswold,
*			 by permission of the author.
*	----------------------------------------------------------------
*
*	Truncate.  Returns an array which contains the first N elements
*	of the argument array, A.  Fails if N <= 0.
*
	DEFINE("TRUNC(A,N)I")					:(TRUNC_END)

TRUNC	TRUNC	=	GT(N,0) ARRAY(N)			:F(FRETURN)
TRUNC1	I	=	I + 1
	TRUNC[I]	=	A[I]				:F(RETURN)S(TRUNC1)
TRUNC_END

*	Extend.  Returns an array which is the argument array A extended by
*	an additional N elements.  Array A is copied into the first part of
*	the new array.
	DEFINE("EXTEND(A,N)I")					:(EXTEND_END)

EXTEND	EXTEND	=	ARRAY(PROTOTYPE(A) + N)
EXTND1	I	=	I + 1
	EXTEND[I]	=	A[I]				:S(EXTND1)F(RETURN)
EXTEND_END
