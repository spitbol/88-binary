; (c) COPYRIGHT 1985, 1994 - CATSPAW, INCORPORATED
; ALL RIGHTS RESERVED.
; USE OF THIS SOURCE CODE IS GOVERNED BY A BSD-STYLE
; LICENSE THAT CAN BE FOUND IN THE LICENSE FILE.

* LTRIM.INC - perform a TRIM on the left end of a string
*
*
*   Usage:
*	Result = LTRIM(S1)
*   or  Result = LTRIM(S1,S2)                                   
*
*   Where:
*	S1 = String to trim
*	S2 = optional one-character string with character to trim
*	
*	If S2 is omitted or null, then blanks and tab characters are
*	trimmed from the beginning of S1.
*
*	If S2 is longer than 1 character, only the first character
*	is used.
*
*   Output:
*	Left trimmed copy of first argument
*
	TERMINAL = ~LOAD("LTRIM(STRING,STRING)STRING")
+		"Cannot load LTRIM external function"	:S(END)
