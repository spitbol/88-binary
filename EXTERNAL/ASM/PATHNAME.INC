* (c) COPYRIGHT 1985, 1994 - CATSPAW, INCORPORATED
* ALL RIGHTS RESERVED.
* USE OF THIS SOURCE CODE IS GOVERNED BY A BSD-STYLE
* LICENSE THAT CAN BE FOUND IN THE LICENSE FILE.

* PATHNAME.INC - emulate SNOBOL4+ PATHNAME function that returns
*		 the file name of the file associated with an I/O channel.
*
*
*  Usage:
*	Result = PATHNAME(channel)
*
*  where channel is the 2nd argument to the INPUT or OUTPUT function.
*
*  Bug: Does not return the name of a file that has been specified on
*	the command line or via an environment variable.
*
	&ERRLIMIT = &ERRLIMIT + 1
	PATHNAME_TEMP = SETEXIT(.PATHNAME_FAIL)
	LOAD("PATHNAME(FILE)STRING")			:(PATHNAME_END)
PATHNAME_FAIL	DEFINE("PATHNAME()")
	CODE("PATHNAME TERMINAL = 'PATHNAME external function "
+		"not loaded' :(FRETURN)")
	&ERRLIMIT = &ERRLIMIT + 1
PATHNAME_END SETEXIT(PATHNAME_TEMP)
	&ERRLIMIT = &ERRLIMIT - 1
