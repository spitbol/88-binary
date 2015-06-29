* (c) COPYRIGHT 1985, 1994 - CATSPAW, INCORPORATED
* ALL RIGHTS RESERVED.
* USE OF THIS SOURCE CODE IS GOVERNED BY A BSD-STYLE
* LICENSE THAT CAN BE FOUND IN THE LICENSE FILE.

* X.INC - Functions to maintain 2-byte integers in an external block.
*
* An array is converted to an external block.
* Integers are stored as pure 16-bit values in slots of the external block.
* XPUT and XGET to and from the external block follow standard array
* conventions of failing if the subscript is out of range.
*
* Functions available to caller:
*
* X = XMAKE(N) - create and return an N-element external block.
* XPUT(I,J,X) - store I in X[J].
* I = XGET(J,X) - retrieve integer in X[J].
*
*
	LOAD("XCREATE(VECTOR)")
	LOAD("XGET(INTEGER,EXTERNAL)INTEGER")
	LOAD("XPUT(INTEGER,INTEGER,EXTERNAL)")
*
	DEFINE("XMAKE(N)")			:(XMAKE_END)
XMAKE	XMAKE = ARRAY(N - 1)
	XCREATE(XMAKE)				:S(RETURN)F(FRETURN)
XMAKE_END

