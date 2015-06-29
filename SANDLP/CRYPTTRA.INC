*	Cryptography by character transposition.
*
*	From STRING AND LIST PROCESSING IN SNOBOL4 by Ralph E. Griswold,
*			 by permission of the author.
*	----------------------------------------------------------------
*
*	(c) Copyright 1985 - Catspaw, Incorporated
*
*	The prefix EN is used for the function which ENcodes a message,
*	and DE is used for the function which DEcodes an encrypted message.
*
*	In a transposition cipher, the characters of the message are
*	rearranged.  Since many of these methods had mechanical origins,
*	the transpositions tend to be based on geometric figures.  The message
*	is written into the figure using one path, and encrypted by reading
*	it out through a different path.  The write-in process is called
*	'inscription', and the read-out process is called 'transcription'.
*
*	If the message length is longer than the number of positions in the
*	figure, it must be broken into successive sections which are the figure
*	size.  If the last section is short, it is padded with meaningless
*	characters, called 'nulls' (not to be confused with the null string).
*
*	The inscription and transcription paths may be specified by assigning
*	a sequence of characters to the figure, and composing a string from
*	the characters along the desired path.  For example, if the figure
*	is a 5 X 5 square, it could be specified as:
*
*		---------------------
*		| A | B | C | D | E |
*		---------------------
*		| F | G | H | I | J |
*		---------------------
*		| K | L | M | N | O |
*		---------------------
*		| P | Q | R | S | T |
*		---------------------
*		| U | V | W | X | Y |
*		---------------------
*
*	Then an inscription path that followed the rows left to right, top
*	to bottom would be specified as 'ABCDEFGHIJKLMNOPQRSTUVWXY', and
*	a transcription path that followed the columns, top to bottom, left
*	to right, would be: 'AFKPUBGLQVCHMRWDINSXEJOTY'.  Of course, more
*	complicated routes could be constructed, and in fact, can be
*	independent of any real figure.
*
*	The REPLACE function was used with substitution ciphers to encode
*	a message using:
*
*		REPLACE(MESSAGE, ALPHABET, CIPHER_ALPHABET)
*
*	The REPLACE function can also be used to perform transpositions:
*
*		REPLACE(TRANSCRIPTION_PATH, INSCRIPTION_PATH, MESSAGE)
*
*	provided MESSAGE is a component of the overall message restricted
*	to the length of the INSCRIPTION_PATH.
*
*	For example:
*
*		S1  =  "123456"	;   S2	=  "135246"
*		R   =  REPLACE(S2,S1,S)
*
*	will transpose string S (of length 6), by placing the odd characters
*	first, followed by the even-positioned characters.
*
*	A transposition key is composed of two components: the inscription
*	path and the transcription path.  The are combined into a single
*	key with the new data type:
*
	DATA("TK(INSCR,TRANS)")
*
*	For the example given above, this would be
*
*	K = TK("ABCDEFGHIJKLMNOPQRSTUVWXY","AFKPUBGLQVCHMRWDINSXEJOTY")
*

*	Function to encode a message M using transposition key K.  The
*	message length must be a multiple of the path length.
*
	DEFINE("ENT(M,K)S")
	SECTIONE	=	LEN(*SIZE(INSCR(K))) . S	:(ENT_END)

ENT	M ? SECTIONE	=					:F(RETURN)
	ENT	=	ENT REPLACE(TRANS(K),INSCR(K),S)	:(ENT)
ENT_END

*	Function to decode a message created by ENT.
*	
	DEFINE("DET(C,K)S")
	SECTIOND	=	LEN(*SIZE(TRANS(K))) . S	:(DET_END)

DET	C ? SECTIOND	=					:F(RETURN)
	DET	=	DET REPLACE(INSCR(K),TRANS(K),S)	:(DET)
DET_END
