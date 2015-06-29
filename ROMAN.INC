* (c) COPYRIGHT 1985, 1994 - CATSPAW, INCORPORATED
* ALL RIGHTS RESERVED.
* USE OF THIS SOURCE CODE IS GOVERNED BY A BSD-STYLE
* LICENSE THAT CAN BE FOUND IN THE LICENSE FILE.

* ROMAN(N) - Convert integer N to Roman numeral form
*	N must be positive and less than 4000
*	An asterisk appears in the result if N >+ 4000
*	The function fails if N is not an integer

	DEFINE('ROMAN(N)UNITS')		:(ROMAN_END)

* Get rightmost digit to UNITS and remove it from N
* Return null result if argument is null
ROMAN	N ? RPOS(1) LEN(1) . UNITS =	:F(RETURN)

* Search for digit, replace with its Roman form.
* Return failing if not a digit.
	'0,1I,2II,3III,4IV,5V,6VI,7VII,8VIII,9IX,' UNITS
+		BREAK(',') . UNITS		:F(FRETURN)

* Convert rest of N and multiply by 10.  Propagate a
* failure return from recursive call back to caller
	ROMAN = REPLACE(ROMAN(N),'IVXLCDM','XLCDM**') UNITS
+			:S(RETURN) F(FRETURN)

ROMAN_END


