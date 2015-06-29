*	Polynomial manipulation.  Some primitive routines to manipulate
*	polynomials.
*
*	From STRING AND LIST PROCESSING IN SNOBOL4 by Ralph E. Griswold,
*			 by permission of the author.
*	----------------------------------------------------------------
*
*	A polynomial is a sum of products expression, where each product
*	consists of an integer coefficient and variables raised to non-
*	negative integer powers.  Consider the polynomial:
*
*	   2 2      2       2
*	-3X Y Z + 5X Y + XYZ  + 3XZ + 7Y -2
*
*	This would be written in fully parenthesized form as:
*
*	((((((((-3*(X^2))*(Y^2))*Z)+((5*(X^2))*Y))+((X*Y)*(Z^2)))-
*	((3*X)*Z))+(7*Y))-2)
*
*	Instead, the following string representation will be used:
*
*	(-3:2,2,1)(5:2,1,0)(1:1,1,2)(-3:1,0,1)(7:0,1,0)(-2:0,0,0)
*
*	That is, the variables are omitted, and only the coefficient and
*	exponents of the terms present are provided.
*
*	Another form used here is the table representation:
*
*	P	=	TABLE()
*	P["2,2,1"]	=	-3
*	P["2,1,0"]	=	5
*	P["1,1,2"]	=	1
*	P["1,0,1"]	=	-3
*	P["0,1,0"]	=	7
*	P["0,0,0"]	=	-2
*

*	Function to convert the poly string form to table form.
*
	DEFINE("STPOLY(S)EXPN,COEFF")
	TERM	=	"(" BREAK(":") . COEFF LEN(1)
+			 BREAK(")") . EXPN LEN(1)		:(STPOLY_END)

STPOLY	STPOLY	=	TABLE()
STPOL1	S ? TERM	=					:F(RETURN)
	STPOLY[EXPN]	=	COEFF				:(STPOL1)
STPOLY_END

*	Function to convert a polynomial from table form to string form:
*
	DEFINE("POLSTR(P)I")					:(POLSTR_END)

POLSTR	P	=	CONVERT(P,"ARRAY")			:F(FRETURN)
POLST1	I	=	I + 1
	POLSTR	=	POLSTR "(" P[I,2] ":" P[I,1] ")"
+								:S(POLST1)F(RETURN)
POLSTR_END

*	Function to add two polynomials that are in table form.
*
	DEFINE("ADPOLY(P1,P2)I")				:(ADPOLY_END)

ADPOLY	P1	=	CONVERT(CONVERT(P1,"ARRAY"),"TABLE")	:F(ADPOL3)
	P2	=	CONVERT(P2,"ARRAY")			:F(ADPOL2)
	I	=	1
ADPOL1	P1[P2[I,1]]	=	P1[P2[I,1]] + P2[I,2]		:F(ADPOL2)
	I	=	I + 1					:(ADPOL1)
ADPOL2	ADPOLY	=	P1					:(RETURN)
ADPOL3	ADPOLY	=	P2					:(RETURN)
ADPOLY_END

*	Function used by the poly multiply routine.  It adds
*	two exponents together.
*
	DEFINE("ADEXPT(X1,X2)")
	EXP1 =	BREAK(",") . E1 LEN(1) | (LEN(1) REM) . E1
	EXP2 =	BREAK(",") . E2 LEN(1) | (LEN(1) REM) . E2	:(ADEXPT_END)

ADEXPT	X1 ? EXP1	=					:F(ADEX1)
	X2 ? EXP2	=					:F(ERROR)
	ADEXPT	=	ADEXPT "," E1 + E2			:(ADEXPT)
ADEX1	ADEXPT	","	=					:(RETURN)
ADEXPT_END

*	Function to multiply two polynomials in table form.
*
	DEFINE("MLPOLY(P1,P2)I,J,X,C,E")			:(MLPOLY_END)

MLPOLY	P1	=	CONVERT(P1,"ARRAY")			:F(RETURN)
	P2	=	CONVERT(P2,"ARRAY")			:F(RETURN)
	MLPOLY	=	TABLE()
MLP1	I	=	I + 1
	X	=	P1[I,1]					:F(RETURN)
	C	=	P1[I,2]
	J	=	0
MLP2	J	=	J + 1
	E	=	ADEXPT(X,P2[J,1])			:F(MLP1)
	MLPOLY[E]	=	MLPOLY[E] + C * P2[J,2]		:(MLP2)
MLPOLY_END

*	Function to produce a copy of a polynomial.
*	Argument and result are in table form.
*
	DEFINE("CPYPOL(P)")					:(CPYPOL_END)

CPYPOL	CPYPOL	=  CONVERT(COPY(CONVERT(P,"ARRAY")),"TABLE")	:S(RETURN)F(FRETURN)
CPYPOL_END
