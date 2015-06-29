*	Functions to manipulate trees in which each node can have
*	an arbitrary number of subtrees.  A node has a value, a pointer
*	to its leftmost child (if any), its right sibling (if any), and
*	its parent (if any).
*
*	From STRING AND LIST PROCESSING IN SNOBOL4 by Ralph E. Griswold,
*			 by permission of the author.
*	----------------------------------------------------------------
*
*	A tree node is defined with the data statement:
*
	DATA("TNODE(VALUE,LSON,RSIB,FATHER)")

*	The root node may be created with TREE = TNODE(V).

*	Add subtree N2 as the child of node N1.  N2 is added to the 'left'
*	of any existing children of N1.
*
	DEFINE("ADDSON(N1,N2)")					:(ADDSON_END)

ADDSON	RSIB(N2)	=	LSON(N1)
	FATHER(N2)	=	N1
	LSON(N1)	=	N2				:(RETURN)
ADDSON_END


*	Add subtree N2 as the right sibling of node N1.  It is inserted between
*	N1 and any existing right sibling it might have.
*
	DEFINE("ADDSIB(N1,N2)")					:(ADDSIB_END)

ADDSIB	RSIB(N2)	=	RSIB(N1)
	RSIB(N1)	=	N2
	FATHER(N2)	=	FATHER(N1)			:(RETURN)
ADDSIB_END


*	Function to convert an expression in prefix form to a tree.  Unlike
*	binary trees, n-ary operators can be represented.  The expression
*	3*F(X,Y,-12)+Z is represented in prefix notation as
*	+(*(3,F(X,Y,-(12)),Z)).
*
	DEFINE("TREE(S)T,X,Y,Z")
	MANY	=	"(" BAL . X "," BAL . Y ")"
	ONE	=	"(" BAL . X ")"
	TFORM	=	BREAK("(") . S (MANY | ONE)
	NEXT	=	POS(0) BAL . Z ","			:(TREE_END)

TREE	S ? TFORM
	TREE	=	TNODE(S)
	T	=	DIFFER(X) TREE(X)			:F(RETURN)
	ADDSON(TREE,T)
TREE1	IDENT(Y)						:S(RETURN)
	Y ? NEXT	=					:F(TREE2)
	ADDSIB(T,TREE(Z))
	T	=	RSIB(T)					:(TREE1)
TREE2	ADDSIB(T,TREE(Y))					:(RETURN)
TREE_END


*	Function to convert a tree back to prefix string form.
*
	DEFINE("TEXP(T)")					:(TEXP_END)

TEXP	TEXP	=	VALUE(T)
	T	=	DIFFER(LSON(T)) LSON(T)			:F(RETURN)
	TEXP	=	TEXP "(" TEXP(T)
TEXP1	T	=	DIFFER(RSIB(T)) RSIB(T)			:F(TEXP2)
	TEXP	=	TEXP "," TEXP(T)			:(TEXP1)
TEXP2	TEXP	=	TEXP ")"				:(RETURN)
TEXP_END


*	Function to assist in traversing a tree.  Given a node as argument,
*	it returns a successor node according to the following priority scheme.
*	1. Left son if possible.
*	2. Right sibling if possible.
*	3. Right sibling of parent if possible.
*	4. Fails when the root node is reached.
*
	DEFINE("TNEXT(N)")					:(TNEXT_END)

TNEXT	TNEXT	=	DIFFER(LSON(N)) LSON(N)			:S(RETURN)
TNEXT1	TNEXT	=	DIFFER(RSIB(N)) RSIB(N)			:S(RETURN)
	N	=	DIFFER(FATHER(N)) FATHER(N)		:S(TNEXT1)F(FRETURN)
TNEXT_END


*	Function to left-list a tree, starting from some node, T.
*
	DEFINE("TLIST(T)")					:(TLIST_END)

TLIST	OUTPUT	=	VALUE(T)
	T	=	TNEXT(T)				:S(TLIST)F(RETURN)
TLIST_END


*	Function to count the number of nodes in a tree.
*
	DEFINE("TSIZE(T)")					:(TSIZE_END)

TSIZE	TSIZE	=	IDENT(T) 0				:S(RETURN)
	TSIZE	=	1
TSIZE1	T	=	TNEXT(T)				:F(RETURN)
	TSIZE	=	TSIZE + 1				:(TSIZE1)
TSIZE_END


*	Function to obtain the LEFT sibling of the argument node.
*	Function fails if there isn't one.
*
	DEFINE("LSIB(NODE)")					:(LSIB_END)

LSIB	IDENT(FATHER(NODE))					:S(FRETURN)
	LSIB	=	LSON(FATHER(NODE))
	IDENT(LSIB,NODE)					:S(FRETURN)
LSIB1	IDENT(RSIB(LSIB),NODE)					:S(RETURN)
	LSIB	=	RSIB(LSIB)				:(LSIB1)
LSIB_END
