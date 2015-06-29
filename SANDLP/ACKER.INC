*	Ackermann function.  This function was used to disprove a conjecture
*	in number theory by the mathematician David Hilbert.  It is not a
*	'primitive-recursive' function, because it grows faster than any
*	'primitive-recursive' function.  It can only be used in SPITBOL with
*	very small integer arguments, because it quickly causes stack overflow.
*
*	The function APROFL will produce a histogram of the function call depth.
*	Try calling it with APROFL(3,2).
*
*	From STRING AND LIST PROCESSING IN SNOBOL4 by Ralph E. Griswold,
*			 by permission of the author.
*	----------------------------------------------------------------
*
	DEFINE("ACKER(M,N)")					:(ACKER_END)

ACKER	ACKER	=	EQ(M,0) N + 1				:S(RETURN)
	ACKER	=	EQ(N,0) ACKER(M - 1,1)			:S(RETURN)
	ACKER	=	ACKER(M - 1, ACKER(M,N - 1))		:(RETURN)
ACKER_END

	DEFINE("APROFL(M,N)")
	DEFINE("ADEPTH(M,N)")
	B	=	DUPL(" ",9)
	TENS	=	B 1 B 2 B 3 B 4 B 5 B 6 B 7
	DIGITS	=	DUPL("1234567890",7)			:(APROFL_END)

APROFL	OUTPUT	=
	OUTPUT	=	"PROFILE OF A(" M "," N ")"
	OUTPUT	=
	OUTPUT	=	TENS
	OUTPUT	=	DIGITS
	CFNCLEVEL	=	&FNCLEVEL
	ADEPTH(M,N)
	OUTPUT	=						:(RETURN)

ADEPTH	OUTPUT	=	DUPL("X",&FNCLEVEL - CFNCLEVEL)
	ADEPTH	=	EQ(M,0) N + 1				:S(RETURN)
	ADEPTH	=	EQ(N,0) ADEPTH(M - 1,1)			:S(RETURN)
	ADEPTH	=	ADEPTH(M - 1,ADEPTH(M,N - 1))		:(RETURN)
APROFL_END
