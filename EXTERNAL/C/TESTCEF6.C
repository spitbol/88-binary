/*
  (c) COPYRIGHT 1985, 1994 - CATSPAW, INCORPORATED
  ALL RIGHTS RESERVED.
  USE OF THIS SOURCE CODE IS GOVERNED BY A BSD-STYLE
  LICENSE THAT CAN BE FOUND IN THE LICENSE FILE.
*/
/*
 * testcef6.c
 *
 * Test access to arguments and return of far external data block.
 * 	LOAD("TESTCEF6(INTEGER,REAL,STRING,OTHER)")
 *
 * 	Call with TESTCEF6(100, 1000.0, "ABCD")
 *
 * 	Returns far external data block if first three arguments were found
 *  as expected on the first call, "OK" on second call.
 * 	Otherwise a message about which argument was bad.
 */

#include "system.h"
#include "extrn88.h"
#include <string.h>

#define testarg1 100
#define testarg2 1000.0
#define testarg3 "ABCD"

#define xbufsiz 2000
char buffer[xbufsiz];

entry(TESTCEF6)(presult, pinfo, parg4, parg3, larg3, rarg2, iarg1)
long	   		iarg1;			 /* arg1 integer						*/
double	   		rarg2;			 /* arg2 real number					*/
word	   		larg3;			 /* arg3 length							*/
char far   		*parg3;			 /* pointer to arg3 string				*/
union block far *parg4;			 /* pointer to unconverted arg4 block	*/
misc far    	*pinfo;		     /* pointer to misc info	*/
union block far	*presult;		 /* pointer to result area	*/
{
	char far *p;
	int		 i;

	if (iarg1 != testarg1)
		return retstrn("First argument not integer 100", presult);
	
	if (rarg2 != testarg2)
		return retstrn("Second argument not real 1000.0", presult);

	if (larg3 != strlen(testarg3))
		return retstrn("Third argument string length wrong", presult);

	if (strncmpfn(parg3, testarg3, larg3))
		return retstrn("Third argument not string 'ABCD'", presult);

	/*
	 *  Test if arg4 is the null string (first call).  Note that arg4
	 *  is unconverted, so we work with raw SPITBOL data blocks.
	 */

	if (parg4->scb.sctyp == sc) {
		if (parg4->scb.sclen != 0)
			return retstrn("Fourth argument was not null string", presult);
		/*
		 * This is the first call, and with null string fourth argument.
		 * Create xbufsiz-byte far external block.
		 */
		p = (char far *)buffer;
		for (i = 0; i < xbufsiz; i++)
			*p++ = (char) i;
		presult->fxb.fxptr = (void far *)buffer;	/* return pointer to data */
		presult->fxb.fxlen = xbufsiz;
		return BL_FX;
		}
	else if (parg4->xnb.xntyp == xn) {
		/*
		 * Fourth argument is external data type.
		 */
		if (parg4->xnb.xnlen != xbufsiz + 2*sizeof(word))
			return retstrn("Fourth argument (external data) size incorrect", presult);
		p = (char far *)parg4->xnb.xnu.xndta;
		for (i = 0; i < xbufsiz; i++)
			if (*p++ != (char)i)
				return retstrn("Fourth argument (external data) contents bad", presult);
		return retstrn("OK", presult);
		}
   return retstrn("Fourth argument not external data", presult);
}
