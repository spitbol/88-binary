*	This function sorts the members of a table using a Shell sort method.
*	The general idea is to try to move out-of-order elements large
*	distances quickly.  A straight-line insertion sort is performed on
*	a series of sub-lists of the master list.  See Comm. of the ACM,
*	July, 1959 for Shell's original article, or Knuth, The Art of
*	Computer Programming, Vol. 3.
*
*	A table is converted to a two column array, with the first column
*	containing the table keys, and the second column containing the
*	entry values.  Sorting is not particularly efficient in SNOBOL4.
*	The built-in SORT function should be used instead.
*
*	The second argument to the function is either a 1 or 2, to specify
*	sorting on the keys or the entry values, respectively.  It defaults
*	to 1 if omitted.
*
*	The third argument is a string specifying the comparison function
*	to be applied to table elements.  It defaults to 'LGT', the lexical
*	compare function, which is suitable for strings.  'GT' could be used
*	if the entries are numeric.
*
*	The result returned is the array created from the argument table.
*	The function fails if the table could not be converted to an array.
*
*	This program is for illustrative purposes only.  The SPITBOL built-in
*	SORT and RSORT functions run many times faster.
*
*	From STRING AND LIST PROCESSING IN SNOBOL4 by Ralph E. Griswold,
*			 by permission of the author.
*	----------------------------------------------------------------
*
	DEFINE("SSORT(TABLE,C,P)I,N,M,J,G,K,T1,T2")
	ALEN	=	BREAK(",") . N				:(SORT_END)

SSORT	SSORT	=	CONVERT(TABLE,"ARRAY")			:F(FRETURN)
	C	=	IDENT(C) 1
	P	=	IDENT(P) "LGT"
	OPSYN("CMP",P)
	PROTOTYPE(SSORT) ? ALEN
	G	=	N

SORTG	G	=	GT(G,1) G / 2				:F(RETURN)
	M	=	N - G
SORTK	K	=	0
	I	=	1
SORTJ	J	=	I + G
	CMP(SSORT[I,C],SSORT[J,C])				:F(SORTI)
	T1	=	SSORT[I,1]
	T2	=	SSORT[I,2]
	SSORT[I,1]	=	SSORT[J,1]
	SSORT[I,2]	=	SSORT[J,2]
	SSORT[J,1]	=	T1
	SSORT[J,2]	=	T2
	K	=	K + 1
SORTI	I	=	LT(I,M) I + 1				:S(SORTJ)
	GT(K,0)							:S(SORTK)F(SORTG)
SORT_END
