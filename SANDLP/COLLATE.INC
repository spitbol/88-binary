*	Interleave the characters of two equi-length strings.
*
*	Result string is obtained by taking characters alternately from
*	the two argument strings.  This is a sophisticated approach, using
*	the REPLACE function.  It trades a high initialization time
*	for a faster running time.  A more simplistic (and slower)
*	version is also given below.
*
*	From STRING AND LIST PROCESSING IN SNOBOL4 by Ralph E. Griswold,
*			 by permission of the author.
*	----------------------------------------------------------------
*
	DEFINE('COLLATE(S1,S2)H,T,C,T1,T2')
*
*	Blend first half of alphabet with second half:
	&ALPHABET ? LEN(128) . H REM . T
COL1	H ? LEN(1) . C1	=					:F(COL2)
	T ? LEN(1) . C2	=
	CALPHABET	=	CALPHABET C1 C2			:(COL1)
*
*	Define some patterns for use later:
COL2	CP1	=	LEN(*SIZE(S1)) . H TAB(128) LEN(*SIZE(S2)) . T
	CP2	=	LEN(*(SIZE(S1) + SIZE(S2))) . C
	CP3	=	LEN(128) . S1 REM . T1
	CP4	=	LEN(128) . S2 REM . T2			:(COLLATE_END)

COLLATE	&ALPHABET ? CP1						:F(COLOVR)
	CALPHABET ? CP2
	COLLATE	=	REPLACE(C,H T,S1 S2)			:(RETURN)

*	Here if S1 or S2 are greater than 128 characters in length.  Use recursion.
COLOVR	S1 ? CP3
	S2 ? CP4
	COLLATE	=	REPLACE(CALPHABET,&ALPHABET,S1 S2)
+			COLLATE(T1,T2)				:(RETURN)

COLLATE_END

*	Simplistic COLLATE function.  Strings do not have to be equal length.
*	The residue from the longer string is appended to the result string.
*
*	From STRING AND LIST PROCESSING IN SNOBOL4 by Ralph E. Griswold,
*			 by permission of the author.
*	----------------------------------------------------------------
*
	DEFINE("SCOLLAT(S1,S2)C1,C2")
	CHAR1	=	LEN(1) . C1
	CHAR2	=	LEN(1) . C2				:(SCOLLAT_END)

SCOLLAT	S1 ? CHAR1	=					:F(SCOLL1)
	S2 ? CHAR2	=					:F(SCOLL2)
	SCOLLAT	=	SCOLLAT C1 C2				:(SCOLLAT)
SCOLL1	SCOLLAT	=	SCOLLAT S2				:(RETURN)
SCOLL2	SCOLLAT	=	SCOLLAT C1 S1				:(RETURN)
SCOLLAT_END
