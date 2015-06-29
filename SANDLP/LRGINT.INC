*	Large integer arithmetic.  A long string of integer digits is
*	decomposed into a linked list of smaller segments, each containing
*	a "digit" in a base 10000 system.
*
*	Positive values only.

*	The limiting factor on integer size is stack overflow, from the
*	recursive nature of these routines.  600 digit numbers should
*	be possible with  MaxSPITBOL's default stack size.  Increase
*	the stack size to use larger numbers.
*
*	Adapted from STRING AND LIST PROCESSING IN SNOBOL4 by Ralph E. Griswold,
*			 by permission of the author.
*	------------------------------------------------------------------------
*

*	The data type used for each segment is
*
	DATA("LRGINT(SEGMENT,NEXT)")

*	Convert a string of digits to a LRGINT.
*
*
	DEFINE("STRLRG(S)R")
	BASE	=	10000
	WIDTH	=	SIZE(BASE) - 1
	MAXIP	=	RTAB(WIDTH) . S REM . R			:(STRLRG_END)

STRLRG	S ? MAXIP						:F(STRLR1)
	STRLRG	=	LRGINT(R,STRLRG(S))			:(RETURN)
STRLR1	STRLRG	=	DIFFER(S) LRGINT(S)			:(RETURN)
STRLRG_END

*	Convert a LRGINT to its string representation:
*
	DEFINE("LRGSTR(L)")					:(LRGSTR_END)

LRGSTR	LRGSTR	=	SEGMENT(L)				:F(RETURN)
	L	=	DIFFER(NEXT(L)) NEXT(L)			:F(RETURN)
	LRGSTR	=	LRGSTR(L) LPAD(LRGSTR,WIDTH,0)		:(RETURN)
LRGSTR_END


*	Convert an integer value to a large integer data type:
*
	DEFINE("INTLRG(I)")					:(INTLRG_END)

INTLRG	INTLRG	=	LRGINT(REMDR(I,BASE))
	NEXT(INTLRG) = GE(I,BASE) INTLRG(I / BASE)		:(RETURN)
INTLRG_END


*	Add two large integers.  C is a carry digit used internally.
*
	DEFINE("ADDLRG(L1,L2,C)")				:(ADDLRG_END)

ADDLRG	ADDLRG	=	IDENT(L1) L2				:S(ADINTC)
	ADDLRG	=	IDENT(L2) L1				:S(ADINTC)
	ADDLRG	=	SEGMENT(L1) + SEGMENT(L2) + C
	ADDLRG	=	LRGINT(REMDR(ADDLRG,BASE),ADDLRG(NEXT(L1),
+			NEXT(L2),ADDLRG / BASE))		:(RETURN)
ADINTC	EQ(C,0)							:S(RETURN)
	ADDLRG	=	ADDLRG(ADDLRG,LRGINT(C))		:(RETURN)
ADDLRG_END

*	Multiply two large integers:
*
	DEFINE("MULLRG(L1,L2)")					:(MULLRG_END)

MULLRG	MULLRG	=	DIFFER(L1) DIFFER(L2) SEGMENT(L1) *
+			SEGMENT(L2)				:F(RETURN)
	MULLRG	=	LRGINT(REMDR(MULLRG,BASE),ADDLRG(
+			MULLRG(L1,NEXT(L2)),MULLRG(NEXT(L1),LRGINT(
+			SEGMENT(L2))),MULLRG / BASE))	:(RETURN)
MULLRG_END
