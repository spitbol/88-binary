*	Rational number package.
*
*	A rational number consists of a fraction of the form P/Q, where
*	P and Q are integer values.  A new SNOBOL4 data type is defined
*	to contain rational numbers in this form.
*
*	Functions are provided to convert a string to a rational and back,
*	to find the greatest common division, to reduce a rational number
*	to a simpler form, and to add and multiply rational numbers.
*
*	From STRING AND LIST PROCESSING IN SNOBOL4 by Ralph E. Griswold,
*			 by permission of the author.
*	----------------------------------------------------------------
*

*	The data type used to hold the numerator and denominator of the
*	fraction is:
*
	DATA("RATIONAL(N,D)")

*	Function to find the greatest common denominator of two integers.
*
	DEFINE("GCD(N,M)R")					:(GCD_END)

GCD	GCD	=	EQ(N,0) M				:S(RETURN)
	R	=	REMDR(M,N)
	GCD	=	EQ(R,0) N				:S(RETURN)
	M	=	N
	N	=	R					:(GCD)
GCD_END

*	Function to reduce its rational argument to lowest terms.
*	In addition to reducing by the greatest common denominator,
*	the denominator is forced to be positive.
*
	DEFINE("REDUCE(R)C")					:(REDUCE_END)

REDUCE	C	=	GCD(N(R),D(R))
	REDUCE	=	RATIONAL(N(R) / C,D(R) / C)
	N(REDUCE)	=	LT(D(REDUCE),0) -N(REDUCE)	:F(RETURN)
	D(REDUCE)	=	-D(REDUCE)			:(RETURN)
REDUCE_END


*	Function to convert a string of the form '[+-]INTEGER/[+-]INTEGER'
*	to rational data type.  Function fails if the rational form is
*	not satisfied by the string.
*
	DEFINE("STRRTL(S)N,D")
	INTEGER	=   (ANY("+-") | '') SPAN("0123456789")
	RTLPAT	=   POS(0) INTEGER . N "/" INTEGER . D RPOS(0)	:(STRRTL_END)

STRRTL	S ? RTLPAT						:F(FRETURN)
	STRRTL	=	REDUCE(RATIONAL(N,D))			:(RETURN)
STRRTL_END


*	Function to convert a rational data type value to string form:
*
	DEFINE("RTLSTR(R)")					:(RTLSTR_END)

RTLSTR	RTLSTR	=	N(R) "/" D(R)				:(RETURN)
RTLSTR_END


*	Function to multiply two rational numbers, and return the
*	rational result.
*
	DEFINE("MULRTL(R1,R2)")					:(MULRTL_END)

MULRTL	MULRTL	=	REDUCE(RATIONAL(N(R1) * N(R2),
+			D(R1) * D(R2)))				:(RETURN)
MULRTL_END


*	Function to divide two rational numbers R1/R2, and return the
*	rational result.
*
	DEFINE("DIVRTL(R1,R2)")					:(DIVRTL_END)

DIVRTL	DIVRTL	=	REDUCE(RATIONAL(N(R1) * D(R2),
+			D(R1) * N(R2)))				:(RETURN)
DIVRTL_END


*	Function to add two rational numbers, and return the
*	rational result.
*
	DEFINE("ADDRTL(R1,R2)")					:(ADDRTL_END)

ADDRTL	ADDRTL	=	REDUCE(RATIONAL(N(R1) * D(R2) + N(R2) * D(R1),
+			D(R1) * D(R2)))				:(RETURN)
ADDRTL_END


*	Function to negate a rational number.
*
	DEFINE("NEGRTL(R)")					:(NEGRTL_END)

NEGRTL	NEGRTL	=	RATIONAL(-N(R), D(R))			:(RETURN)
NEGRTL_END


*	Function to subtract two rational numbers R1-R2, and return
*	the rational result.
*
	DEFINE("SUBRTL(R1,R2)")					:(SUBRTL_END)

SUBRTL	SUBRTL	=	ADDRTL(R1, NEGRTL(R2))			:(RETURN)
SUBRTL_END

*	Functions for complex rational numbers of the form:
*
*	P/Q+S/TI
*
*
*	The data type used to hold the real and imaginary rational components:
*
	DATA("CPXRTL(RR,IR)")

-STRCXR
*	Function to convert a string of the form:
*	'[+-]INTEGER/[+-]INTEGER[+-]INTEGER/[+-]INTEGERI' to complex
*	rational data type.  Function fails if the complex rational form is
*	not satisfied by the string.  The real and imaginary parts
*	are each optional.
*
	DEFINE("STRCXR(S)NR,DR,NI,DI")
	RPAT	=   INTEGER . NR "/" INTEGER . DR
	IPAT	=   INTEGER . NI "/" INTEGER . DI ("I" | "i")
	CXRPAT	=   POS(0) (RPAT | IPAT | RPAT IPAT) RPOS(0)	:(STRCXR_END)

STRCXR	DR	=	'1'
	DI	=	'1'
	NR	=	'0'
	NI	=	'0'
	S ? CXRPAT						:F(FRETURN)
	STRCXR	=   CPXRTL(REDUCE(RATIONAL(NR,DR)),
+		    REDUCE(RATIONAL(NI,DI)))			:(RETURN)
STRCXR_END


*	Function to convert a complex rational to string form.
*
	DEFINE("CXRSTR(X)S")					:(CXRSTR_END)

CXRSTR	CXRSTR	=	RTLSTR(RR(X))
	S	=	RTLSTR(IR(X))
	S ? "-"							:S(CXRM)
	CXRSTR	=	CXRSTR "+" S "I"			:(RETURN)
CXRM	CXRSTR	=	CXRSTR S "I"				:(RETURN)
CXRSTR_END


*	Function to add two complex rational numbers.
*
	DEFINE("ADDCXR(X1,X2)")					:(ADDCXR_END)

ADDCXR	ADDCXR	=	CPXRTL(ADDRTL(RR(X1),RR(X2)),
+			ADDRTL(IR(X1),IR(X2)))			:(RETURN)
ADDCXR_END


*	Function to multiply two complex rational numbers.
*
	DEFINE("MULCXR(X1,X2)")					:(MULCXR_END)

MULCXR	MULCXR	=	CPXRTL(ADDRTL(MULRTL(RR(X1),RR(X2)),
+			NEGRTL(MULRTL(IR(X1),IR(X2)))),
+			ADDRTL(MULRTL(RR(X1),IR(X2)),MULRTL(IR(X1),RR(X2))))
+								:(RETURN)
MULCXR_END
