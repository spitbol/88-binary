*	Rotate a string N positions.
*	N > 0 for rotation to right.
*	N < 0 for rotation to left.
*
*	From STRING AND LIST PROCESSING IN SNOBOL4 by Ralph E. Griswold,
*			 by permission of the author.
*	----------------------------------------------------------------
*
	DEFINE('ROTATE(ROTATE,N)H,T')
	ROTPAT = (*LT(N,0) LEN(*(-N)) . H | RTAB(*N) . H) REM . T :(ROTATE_END)
ROTATE	N = DIFFER(ROTATE) REMDR(N,SIZE(ROTATE))		  :F(RETURN)
	ROTATE ? ROTPAT = T H					  :(RETURN)
ROTATE_END
