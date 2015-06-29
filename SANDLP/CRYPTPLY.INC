*	Cryptography by polyliteral substitution.
*
*	From STRING AND LIST PROCESSING IN SNOBOL4 by Ralph E. Griswold,
*			 by permission of the author.
*	----------------------------------------------------------------
*
*	The prefix EN is used for the function which ENcodes a message,
*	and DE is used for the function which DEcodes an encrypted message.
*
*	The amount of memory used, and the processing time required can
*	be substantially reduced by using a restricted message alphabet.
*	Here we use the entire 256 ASCII character set.
*
	MALPHABET	=	&ALPHABET
*
*	A polyliteral substitution is one in which multiple characters
*	are substituted for each character of the message.  These functions
*	make use of the COLLATE and DECOLLATE, which are defined elsewhere.
*
*	In a biliteral substitution, two characters are substituted for
*	each message character.  Consider a key composed of two strings,
*	where one contains the first character of the pair to be substituted,
*	and the other contains the second character of the pair:
*
	DATA("BLK(S1,S2)")
*
*	The encoding key is then:     EK = BLK(S1,S2)
*

*	Function to perform biliteral encoding of a message M, using encoding
*	key EK.  ENMAS is required from file CryptSub.inc.  The message
*	character set is specified by MALPHABET.
*
	DEFINE("ENBLS(M,EK)")					:(ENBLS_END)

ENBLS	ENBLS	=	COLLATE(ENMAS(M,S1(EK)),ENMAS(M,S2(EK))) :(RETURN)
ENBLS_END

*	Deciphering requires more work.  A 'cipher alphabet' is a string
*	which is as long as the message alphabet, and in which all the
*	characters are different; there are no repeated characters.
*	If S1 or S2 is a cipher alphabet, biliteral substitution is no
*	more secure than a simple monoalphabetic cipher.
*	For biliteral substitution to work properly, it is NOT required
*	that S1 or S2 be cipher alphabets, only that all the pairs
*	produced from S1 and S2 be unique.  In fact, S1 and S2 can be drawn
*	from an alphabet that is more restricted than the message alphabet,
*	since the number of pairs is greater than the number of letters in
*	S1 or S2.
*

*	Function to decrypt messages if S1 or S2 is a cipher alphabet.
*	Assume S1 is the cipher alphabet:
*
	DEFINE("DEBLSCA(C,EK)")					:(DEBLSCA_END)

DEBLSCA	DEBLSCA	=	REPLACE(DECOLLATE(C,1),S1(EK),MALPHABET) :(RETURN)
DEBLSCA_END

*	The more general function to decrypt biliteral encodings assumes
*	that neither S1 nor S2 is a cipher alphabet.  It is first necessary to
*	construct a table that associates each pair of coded message characters
*	with the plaintext alphabet.  This function constructs a decryption
*	key DK from the encryption key, EK.
*
	DEFINE('DBLK(EK)CH,TALPHABET')
	ONECH	=	LEN(1) . CH				:(DBLK_END)

DBLK	DBLK	=	TABLE(SIZE(MALPHABET))
	TALPHABET	=	MALPHABET

DEK1	TALPHABET ?  ONECH	=				:F(RETURN)
	DBLK[ENBLS(CH,EK)]	=	CH			:(DEK1)
DBLK_END

*	Now it is possible to decode a general biliteral message C using
*	decryption key DK.
*
	DEFINE("DEBLS(C,DK)CPAIR")
	TWOCH	=	LEN(2) . CPAIR				:(DEBLS_END)

DEBLS	C ? TWOCH	=					:F(RETURN)
	DEBLS	=	DEBLS DK[CPAIR]				:(DEBLS)
DEBLS_END

*	A method which can be used to construct the strings S1 and S2
*	is to write the message alphabet into a grid, and use scrambled
*	characters from the cipher alphabet as row and column labels:
*
*		  C   A   D   F   E   B
*
*		-------------------------
*	     E	| A | B | C | D | E | F |
*		-------------------------
*	     A	| G | H | I | J | K | L |
*		-------------------------
*	     F	| M | N | O | P | Q | R |
*		-------------------------
*	     D	| S | T | U | V | W | X |
*		-------------------------
*	     C	| Y | Z | 0 | 1 | 2 | 3 |
*		-------------------------
*	     B	| 4 | 5 | 6 | 7 | 8 | 9 |
*		-------------------------
*

*	This function will create a biliteral key for the encoding above.
*	COL and ROW are the column and row labeling strings.
*
	DEFINE("BILT(COL,ROW)CH,S,S1")
	ONECH	=	LEN(1) . CH				:(BILT_END)

BILT	S	=	SIZE(COL)
BILTN	COL ? ONECH	=					:F(BILTR)
	S1	=	S1 DUPL(CH,S)				:(BILTN)
BILTR	BILT	=	BLK(S1,DUPL(ROW,S))			:(RETURN)
BILT_END


*	Function to convert a number string from base 4 to base 2.  This is
*	essentially a biliteral substitution.
*
	DEFINE("QTRBIN(Q)")					:(QTRBIN_END)

QTRBIN	QTRBIN	=	COLLATE(REPLACE(Q,"0123","0011"),
+			REPLACE(Q,"0123","0101"))		:(RETURN)
QTRBIN_END

*	A polygraphic substitution is one in which groups of characters in
*	the plaintext message are replaced by groups of characters from the
*	key.  The problem of creating tables is the combinatorial explosion
*	resulting from a large alphabet.  For example, taking 2-grams from
*	the source message results in 256*256 possible combinations if the
*	entire character set of &ALPHABET is allowed.
