/*
  (c) COPYRIGHT 1985, 1994 - CATSPAW, INCORPORATED
  ALL RIGHTS RESERVED.
  USE OF THIS SOURCE CODE IS GOVERNED BY A BSD-STYLE
  LICENSE THAT CAN BE FOUND IN THE LICENSE FILE.
*/
/*
 * testcef3.c
 *
 * Test access to arguments and return of real number:
 * 	LOAD("TESTCEF3(INTEGER,REAL,STRING)")
 *
 * 	Call with TESTCEF3(100, 1000.0, "ABCD")
 *
 * 	Returns arg 2 minus 1.0 if arguments were found as expected,
 * 	otherwise a message about which argument was bad.
 */

#include "system.h"
#include "extrn88.h"
#include <string.h>

#define testarg1 100
#define testarg2 1000.0
#define testarg3 "ABCD"

entry(TESTCEF3)(presult, pmisc, parg3, larg3, rarg2, iarg1)
long	   		iarg1;			 /* arg1 integer			*/
double	   		rarg2;			 /* arg2 real number		*/
word	   		larg3;			 /* arg3 length				*/
char far   		*parg3;			 /* pointer to arg3 string	*/
misc far    	*pmisc;		     /* pointer to misc info	*/
union block far	*presult;		 /* pointer to result area	*/
{

	if (iarg1 != testarg1)
		return retstrn("First argument not integer 100", presult);

	if (rarg2 != testarg2)
		return retstrn("Second argument not real 1000.0", presult);

	if (larg3 != strlen(testarg3))
		return retstrn("Third argument string length wrong", presult);

	if (strncmpfn(parg3, testarg3, larg3))
		return retstrn("Third argument not string 'ABCD'", presult);

	return retreal(rarg2 - 1.0, presult);	/* Arguments are OK, return arg2-1	*/
}
