*	Cryptanalysis.
*
*	From STRING AND LIST PROCESSING IN SNOBOL4 by Ralph E. Griswold,
*			 by permission of the author.
*	----------------------------------------------------------------
*
*	These programs generate some statistics about a coded message.
*	When loaded with Code.spt and the encryption functions, they
*	can be used interactively to analyze a message.
*
*	Of course, the REPLACE function may be used interactively to make
*	test substitution and transpostions.
*
*	A polyliteral cipher produces a message which has repeated
*	n-character groups.  The number of unique groups suggests
*	the number of characters in the message alphabet.

*	Function to list groups of size two thru five found in the coded
*	message CIPHER.
*
	DEFINE('GROUPS(CIPHER)N,TEXT,NGRUP,S,K')
	GRUP	=	LEN(*N) . S				:(GROUPS_END)

GROUPS	N	=	1
PROC	OUTPUT	=
	TEXT	=	CIPHER
	NGRUP	=	TABLE()
	N	=	LT(N,5) N + 1				:F(RETURN)
NLOOP	TEXT ? GRUP	=					:F(DISP)
	NGRUP[S]	=	NGRUP[S] + 1			:(NLOOP)
DISP	NGRUP	=	SORT(NGRUP)				:F(NONE)
	PROTOTYPE(NGRUP) ? BREAK(",") . K
	OUTPUT	=	"NUMBER OF " N "-GROUPS IS " K
	PRINT(NGRUP)						:(PROC)
NONE	OUTPUT	=	"NUMBER OF " N "-GROUPS IS 0"
GROUPS_END

*	A periodic polyalphabetic substitution will exhibit some periodicity in
*	the encoded message.  Character pairs in the plaintext message will
*	produce character pairs in the coded message.  The distance between
*	such digrams can reveal the period of the encoding key.  This program
*	examines a message for repeated pairs, and prints the distance between
*	them.  When the period is known to be N, the cipher can be 'decollated'
*	into N sections, and each treated as a mono-alphabetic cipher.  Function
*	DIGRAM examines a message CIPHER for periodicities.  DIVCNT is a helper
*	function.
*

	DEFINE('DIGRAM(CIPHER)I,PR,GAP,DIVTBL')
	PAIR	=	TAB(*I) LEN(2) $ PR ARB . GAP *PR	:(DIGRAM_END)

DIGRAM	DIVTBL	=	TABLE()
	I	=	0
NEXTP	CIPHER ? PAIR						:F(NEXTI)
	OUTPUT	=	"REPEATED PAIR " PR " AT DISTANCE " SIZE(GAP) + 2
	DIVCNT(SIZE(GAP) + 2)
NEXTI	I	=	LT(I,SIZE(CIPHER) - 4) I + 1		:S(NEXTP)
	OUTPUT	=
	OUTPUT	=	"TABULATION OF DIVISORS"
	PRINT(SORT(DIVTBL,2,"LT"))				:S(RETURN)
NONE	OUTPUT	=	"THERE ARE NO DIVISORS"			:(RETURN)
DIGRAM_END

	DEFINE('DIVCNT(N)I')					:(DIVCNT_END)

DIVCNT	I	=	1
DIVINC	I	=	LT(I,N) I + 1				:F(RETURN)
	EQ(REMDR(N,I),0)					:F(DIVINC)
	DIVTBL[I]	=	DIVTBL[I] + 1			:(DIVINC)
DIVCNT_END

*	This function will return the argument string with its characters
*	arranged alphabetically.  This makes them readily available for
*	hand anagramming.
*
	DEFINE("CORDER(STRING)CH,T,ALPHA")
	ONECH	=	LEN(1) . CH				:(CORDER_END)

CORDER	T	=	TABLE(SIZE(&ALPHABET))
NEXTC	STRING ? ONECH	=					:F(CORD)
	T[CH]	=	T[CH] CH				:(NEXTC)
CORD	ALPHA	=	&ALPHABET
NEXTA	ALPHA ? ONECH	=					:F(RETURN)
	CORDER	=	CORDER T[CH]				:(NEXTA)
CORDER_END

*	From file Sort.inc
	DEFINE("SORT(TABLE,C,P)I,N,M,J,G,K,T1,T2")
	ALEN	=	BREAK(",") . N				:(SORT_END)

SORT	SORT	=	CONVERT(TABLE,"ARRAY")			:F(FRETURN)
	C	=	IDENT(C) 1
	P	=	IDENT(P) "LGT"
	OPSYN("CMP",P)
	PROTOTYPE(SORT) ? ALEN
	G	=	N

SORTG	G	=	GT(G,1) G / 2				:F(RETURN)
	M	=	N - G
SORTK	K	=	0
	I	=	1
SORTJ	J	=	I + G
	CMP(SORT[I,C],SORT[J,C])				:F(SORTI)
	T1	=	SORT[I,1]
	T2	=	SORT[I,2]
	SORT[I,1]	=	SORT[J,1]
	SORT[I,2]	=	SORT[J,2]
	SORT[J,1]	=	T1
	SORT[J,2]	=	T2
	K	=	K + 1
SORTI	I	=	LT(I,M) I + 1				:S(SORTJ)
	GT(K,0)							:S(SORTK)F(SORTG)
SORT_END

*	From file Concord.spt
	DEFINE("PRINT(A)I")					:(PRINT_END)

PRINT	I	=	I + 1
	OUTPUT	=	A[I,1] " : " A[I,2]			:S(PRINT)F(RETURN)
PRINT_END
