*	Cryptography by character substitution.
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
*	The simplest ciphers are monoliteral substitutions, in which
*	one character is substituted for another.  In a monoalphabetic
*	substitution, the cipher alphabet is formed by some re-arrangement
*	of the characters of the alphabet from which the message is composed.

*	Encode a message by monoalphabetic substitution.  M is the message,
*	and K is the key, or cipher alphabet.  Two possibilities for K are:
*	K = REVERSE(MALPHABET)
*	K = ROTATE(MALPHABET,-3)	(Ceasar's Cipher)
*
	DEFINE("ENMAS(M,K)")					:(ENMAS_END)

ENMAS	ENMAS	=	REPLACE(M,MALPHABET,K)			:(RETURN)
ENMAS_END

*	Decode a coded message C using key K.
*
	DEFINE("DEMAS(C,K)")					:(DEMAS_END)

DEMAS	DEMAS	=	REPLACE(C,K,MALPHABET)			:(RETURN)
DEMAS_END

-ENKAT
*	A keyed alphabet uses a key word or string as the first characters
*	of the cipher alphabet, followed by the remaining characters of the
*	alphabet, in order.  Duplicate letters are discarded.  For example, if
*	the alphabet is restricted to upper case letters, the key word 'SNOBOL'
*	would produce the cipher alphabet SNOBLACDEFGHIJKMPQRTUVWXYZ.
*
*	The function ENKAT returns a cipher alphabet given a key word or string:
*
*	CA	=	ENKAT(KEY)
*
	DEFINE("ENKAT(KEY)")
	REPEAT	=	(LEN(1) $ C BREAK(*C)) . GAP LEN(1)	:(ENKAT_END)

ENKAT	ENKAT	=	KEY MALPHABET
ENK	ENKAT ? REPEAT	=	GAP				:S(ENK)F(RETURN)
ENKAT_END


*	A polyalphabetic substitution is one in which a series of cipher
*	alphabets are used sequentially for each letter of the message
*	to be encoded.
*
*	The cipher alpabets created from the multiple key words are
*	conveniently keep in a ring structure:
*
	DATA("KEYRING(CA,NEXT)")
*
*	Consider a four key cipher created as follows:
*
	K4	=	KEYRING(ENKAT("ENCHILADA"))
	K3	=	KEYRING(ENKAT("LOBOTOMY"),K4)
	K2	=	KEYRING(ENKAT("PIGSKIN"),K3)
	KEY	=	KEYRING(ENKAT("ZEUS"),K2)
	NEXT(K4)	=	KEY

-ENPAS
*	Function to encode a message with a polyalphabetic cipher.  M is the
*	message to encode, KEY is a pointer to the ring structure containing
*	the multiple cipher alphabets.
*
	DEFINE("ENPAS(M,KEY)CH")
	ONECH	=	LEN(1) . CH				:(ENPAS_END)

ENPAS	M ? ONECH	=					:F(RETURN)
	ENPAS	=	ENPAS REPLACE(CH,MALPHABET,CA(KEY))
	KEY	=	NEXT(KEY)				:(ENPAS)
ENPAS_END

-DEPAS
*	Function to decode a message created by ENPAS.
*
	DEFINE("DEPAS(C,KEY)CH")				:(DEPAS_END)

DEPAS	C ? ONECH	=					:F(RETURN)
	DEPAS	=	DEPAS REPLACE(CH,CA(KEY),MALPHABET)
	KEY	=	NEXT(KEY)				:(DEPAS)
DEPAS_END

*	A Vigenere Square is a polyalphabetic substitution in which there
*	are as many cipher alphabets as characters in the alphabet.  There are
*	many ways to construct and use such a square.  The example in the
*	book constructs the first alphabet as a keyed alphabet, using ENKAT.
*	The remaining alphabets are constructed by successive rotations of the
*	keyed alphabet.  The characters of the message to be encoded select
*	the cipher alphabet to be used.  The cipher alphabet for the first
*	message character is selected a priori.  The first message character
*	selects the cipher alphabet to be used for the second message character,
*	the second message character selects the cipher alphabet for the third
*	character, etc.

*	Function to create a Vigenere Square from some key word KEY.  The
*	square is stored as a table, using the first character of each
*	cipher alphabet as the table subscript.  This allows each cipher
*	alphabet to be associatively fetched based on the previous message
*	character.
*
	DEFINE("VSQ(KEY)CH,I,CA,LIMIT")
	ONECH	=	LEN(1) . CH				:(VSQ_END)

VSQ	CA	=	ENKAT(KEY)
	LIMIT	=	SIZE(CA)
	VSQ	=	TABLE(LIMIT)
	I	=	1
VSQ1	CA	ONECH
	VSQ[CH]	=	CA
	I	=	LT(I,LIMIT) I + 1			:F(RETURN)
	CA	=	ROTATE(CA,-1)				:(VSQ1)
VSQ_END

*	To use the Vigenere Square, we need to specify a key word, and
*	a letter to be used to pick the first cipher alphabet.  A data
*	structure to hold the resulting key is:
*
	DATA("AUTOKEY(VSQUARE,FIRST)")

*	The key then is created with:
*
*	K	=	AUTOKEY(VSQ(KEYWORD),LETTER)
*

-ENAUTO
*	A function to encrypt a message M using key K is:
*
	DEFINE("ENAUTO(M,K)V,CA,CH")
	ONECH	=	LEN(1) . CH				:(ENAUTO_END)

ENAUTO	V	=	VSQUARE(K)
	CA	=	V[FIRST(K)]
ENAUTN	M ? ONECH	=					:F(RETURN)
	ENAUTO	=	ENAUTO REPLACE(CH,MALPHABET,CA)
	CA	=	V[CH]					:(ENAUTN)
ENAUTO_END

-DEAUTO
*	A function to decode a message C using key K is:
*
	DEFINE("DEAUTO(C,K)V,CA,CH")				:(DEAUTO_END)

DEAUTO	V	=	VSQUARE(K)
	CA	=	V[FIRST(K)]
DEAUTN	C ? ONECH	=					:F(RETURN)
	CH	=	REPLACE(CH,CA,MALPHABET)
	DEAUTO	=	DEAUTO CH
	CA	=	V[CH]					:(DEAUTN)
DEAUTO_END
