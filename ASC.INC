* (c) COPYRIGHT 1985, 1994 - CATSPAW, INCORPORATED
* ALL RIGHTS RESERVED.
* USE OF THIS SOURCE CODE IS GOVERNED BY A BSD-STYLE
* LICENSE THAT CAN BE FOUND IN THE LICENSE FILE.

* ASC(S) returns ASCII value of first character of string S
* The value returned is an integer between 0 and 255
* The function fails if S is null.
	DEFINE('ASC(S)C')
	ASC_ONE = LEN(1) . C
	ASC_PAT = BREAK(*C) @ASC		:(ASC_END)
ASC	S ASC_ONE				:F(FRETURN)
	&ALPHABET ASC_PAT			:(RETURN)
ASC_END
