* (c) COPYRIGHT 1985, 1994 - CATSPAW, INCORPORATED
* ALL RIGHTS RESERVED.
* USE OF THIS SOURCE CODE IS GOVERNED BY A BSD-STYLE
* LICENSE THAT CAN BE FOUND IN THE LICENSE FILE.

* FACT(N) - Compute N! using recursion.
*	N must be less than 171.0 to prevent real overflow.

	DEFINE('FACT(N)')			:(FACT_END)

*	If argument is 1 or less, return 1 as result
FACT	FACT = LE(N,1) 1			:S(RETURN)

*	Otherwise, result is N * (N-1)!
	FACT = N * FACT(N - 1)			:(RETURN)
FACT_END
