* BinTree.inc 
*	Functions to manipulate a binary tree, in which each node can
*	have a left and right subtree.
*
*	The two functions BTREE and BEXP are provided for demonstration
*	purposes.  The convert between the string form of an expression
*	and its tree representation.  The expression is given is fully
*	parenthesized prefix notation (as created by PREFIX.inc):
*
*	   OP(LEFT)
*	   OP(,RIGHT)
*	   OP(LEFT,RIGHT)
*
*	A typical call to create a tree for S(B*(A-C/D)):
*
*	   B = BTREE("S(*(B,-(A,/(C,D))))")
*
*	The tree can be expanded back to string form and displayed with:
*
*	   OUTPUT = BEXP(B)
*
*
*	From STRING AND LIST PROCESSING IN SNOBOL4 by Ralph E. Griswold,
*			 by permission of the author.
*	----------------------------------------------------------------
*

*	Definition of a tree node:
*
 	DATA("BNODE(VALUE,LEFT,RIGHT,UP)")

*	The initial root node of a tree is created with value V using:
*		TREE = BNODE(V)
*

*	Functions to add node N2 as left or right subtree below node N1.
*
	DEFINE("ADDL(N1,N2)")
	DEFINE("ADDR(N1,N2)")					:(ADD_END)

ADDL	LEFT(N1)  =	N2
ADDU	UP(N2)	  =	N1					:(RETURN)
ADDR	RIGHT(N1) =	N2					:(ADDU)
ADD_END

*	Function to copy a binary tree.
*
	DEFINE("COPYBT(T)")					:(COPYBT_END)

COPYBT	COPYBT	=	COPY(T)
	(DIFFER(LEFT(T)) ADDL(COPYBT,COPYBT(LEFT(T))))
	(DIFFER(RIGHT(T)) ADDR(COPYBT,COPYBT(RIGHT(T))))	:(RETURN)
COPYBT_END

*	Function to convert an arithmetic expression in prefix form to
*	a binary tree.
*
	DEFINE("BTREE(S)L,R")
	TWO	=	"(" BAL . L "," BAL . R ")"
	RONE	=	"(," BAL . R ")"
	LONE	=	"(" BAL . L ")"
	TFORM	=	BREAK("(") . S (TWO | RONE | LONE)	:(BTREE_END)

BTREE	S ? TFORM
	BTREE	=	BNODE(S)
	(DIFFER(L) ADDL(BTREE,BTREE(L)))
	(DIFFER(R) ADDR(BTREE,BTREE(R)))			:(RETURN)
BTREE_END

*	Function to reconstruct a prefix expression from a binary tree.
*
	DEFINE("BEXP(T)L,R")					:(BEXP_END)

BEXP	BEXP	=	VALUE(T)
	L	=	DIFFER(LEFT(T)) BEXP(LEFT(T))
	R	=	DIFFER(RIGHT(T)) "," BEXP(RIGHT(T))
	S	=	L R
	BEXP	=	DIFFER(S) BEXP "(" S ")"		:(RETURN)
BEXP_END

*	Function to add a value V to a tree T by sorting it into place.
*	The first value in the tree becomes the root node.  Subsequent
*	values are placed in the left subtree if they are greater than
*	the root value, and in the right subtree if less than.  Equal
*	values are discarded.
*
*	Create the tree with T = BINTREE()
*
	DATA("BINTREE(ROOT)")
	DEFINE("LEXINS(V,T)N")					:(LEXINS_END)

LEXINS	N	=	ROOT(T)
	ROOT(T)	=	IDENT(N) BNODE(V)			:S(RETURN)
LEXNXT	LGT(VALUE(N),V)						:S(LEXRT)
	IDENT(VALUE(N),V)					:S(RETURN)
	N	=	DIFFER(LEFT(N)) LEFT(N)			:S(LEXNXT)
	ADDL(N,BNODE(V))					:(RETURN)
LEXRT	N	=	DIFFER(RIGHT(N)) RIGHT(N)		:S(LEXNXT)
	ADDR(N,BNODE(V))					:(RETURN)
LEXINS_END

*	Print a tree created by LEXINS.
*
	DEFINE("LEXPRT(T)N,M")					:(LEXPRT_END)

LEXPRT	N	=	DIFFER(ROOT(T)) ROOT(T)			:F(RETURN)
LEXPRD	N	=	DIFFER(RIGHT(N)) RIGHT(N)		:S(LEXPRD)
LEXOUT	OUTPUT	=	VALUE(N)
	N	=	DIFFER(LEFT(N)) LEFT(N)			:S(LEXPRD)
LEXUP	M	=	N
	N	=	DIFFER(UP(N)) UP(N)			:F(RETURN)
	DIFFER(LEFT(N),M)					:S(LEXOUT)F(LEXUP)
LEXPRT_END
