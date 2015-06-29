*	An NGRAM is a string N characters long, drawn from the characters
*	in the ordered set CSET.  The next ngram function 'increments' the
*	rightmost character in its argument by replacing it by its
*	successor character in CSET.  When the last character in CSET has been
*	used, the first character of CSET is chosen, and the next (leftward)
*	character of the argument is 'incremented'.  This is similar to
*	numeric counting in a base whose 'digits' are specified by CSET.
*
*	The NEXTG function 'increments' the argument NGRAM according to the
*	global variable CSET.  The function fails when the 'highest' NGRAM is
*	reached.  That is, the argument NGRAM consists entirely of the last
*	character in CSET.  It is trivial to alter NEXTG to cyclicly restart
*	the sequence using the first character of CSET when this occurs.  To
*	do so, replace the last line with:
*	NEXTG1	NEXTG	=	NEXTG(GRAM) F			:S(RETURN)
*		NEXTG	=	DUPL(F,SIZE(GRAM) + 1)		:(RETURN)
*
*	The NEXTS function extends NEXTG by detecting the 'highest' NGRAM, and
*	returning the 'lowest' (N+1)GRAM instead,  That is, a 'carry' is
*	propagated.
*
*	From STRING AND LIST PROCESSING IN SNOBOL4 by Ralph E. Griswold,
*			 by permission of the author.
*	----------------------------------------------------------------
*

*	DEFINE A SIMPLE CHARACTER SET.
	CSET	=	'ABCD'

	DEFINE("NEXTG(GRAM)C")
	LAST	=	RTAB(1) . GRAM LEN(1) . C
	SCSR	=	BREAK(*C) LEN(1) LEN(1) . C
	CSET ? LEN(1) . F					:(NEXTG_END)

NEXTG	GRAM ? LAST						:F(FRETURN)
	CSET ? SCSR						:F(NEXTG1)
	NEXTG	=	GRAM C					:(RETURN)
NEXTG1	NEXTG	=	NEXTG(GRAM) F				:S(RETURN)F(FRETURN)
NEXTG_END

	DEFINE("NEXTS(STRING)C")				:(NEXTS_END)

NEXTS	NEXTS	=	NEXTG(STRING)				:S(RETURN)
	NEXTS	=	DUPL(F,SIZE(STRING) + 1)		:(RETURN)
NEXTS_END
