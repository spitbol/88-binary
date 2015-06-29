
/*
  Copyright 1992  Mark Emmer.
  All Rights Reserved.
  Use Of this source code is governed by a BSD-style
  license that can be found in the LICENSE file.
*/
#include "extrn88.h"

/*
 * retreal(val, presult) - Return real number
 */
word retreal(double val, union block far *presult)
{
	presult->rcb.rcval = val;
	return BL_RC;
}
