/* 
 *
 *	red black tree - binary search tree {
 *
 * 		bst: at most two children for node { 0, 1, 2 }, left child with lower value than parent,
 * 			 right child with higher value than parent, each node is a binary search subtree. 
 * 			 A bst is not necessarily balanced: it can contain all root's children at its left side ( creating an array ).
 *
 * 		insertion in bst: 1st insert is root, next insertions must fullfil bst requirements.
 * 						  Insertion search always starts at ROOT.
 *
 * 		deletion: node marked for deletion { 1. has 0 children, 2. has 1 child, 3. has 2 children }
 * 				  1. delink and free node
 * 				  2. node replaced with child: link parent to child, delete node
 * 				  3. substitute with its inorder predecesor, OR with its inorder succesor
 * 				  	 inorder predecessor - largest element of left subtree
 * 				  	 inorder succesor - smallest element of right subtree
 *
 *	}
 *
 *  red black tree - *self balancing* bst ( guaranteed Olog(n) time complexity access & insertion )
 *  	( balanced binary tree: height diff. between left and right subtree no more than 1 )
 *
 *  red black tree rules:
 *  	node either red or black ( reserve 1 bit for color )
 *  	root and leaves ( NULL ptrs ) are black
 *		if node == red; its children are black
 *		all paths from node -> NULL leaf have the same number of black nodes
 *
 *
 *	insertions:
 *		1. insert a red node
 *		2. recolor & rotate -> fix rule violations after inserting
 *			. case : BLACK parent - exit
 *			. case : uncle of inserted node is RED - recolor parent, grandparent ( if not ROOT ) & uncle
 *					 and recheck with parent node ( to avoid RED - RED conflicts )
 *			. case : uncle is BLACK - rotate parent at opposite direction with it's parent,
 *					 recolor node's parent & grandparent,
 *					 rotate grandparent at opposite direction of first rotation
 *					 					
 *
 * 	deletion:
 * 		1. binary tree deletion:
 * 			1.1 node to delete with no children - just delete it
 * 			1.2 ( do not delete internal nodes ) - parent nodes are replaced, replace and destroy leaf
 * 			1.3 parent with two children: replace it with ( inorder predecessor ) or ( inorder successor )
 * 		2. red-black tree edits: on swapping, only replace value, color of node is not replaced
 * 			( in deleting a black parent with red child, replace parent's value with child's, parent with new val
 * 			   is still black, then delete red child )
 * 			( recursive replacements - if inorder successor  is not leaf, keep replacing until leaf is found )
 * 		3. * if node to delete is color red, just delete it
 * 		   * if node to delete is black, make it DB ( subs. blackk node for black NIL child ),
 * 				  then recursively try to remove its DB cond.
 * 
 * 		   		case : root is DB - make it single black
 * 		   		case : DB node's sibling and both its children are BLACK
 * 					   remove DB from node, try to make parent black ( if already black, it becomes DB, manage it. )
 * 					   sibling becomes RED
 * 				case : DB node's sibling is RED
 * 					   sibling becomes BLACK, parent becomes RED ( swap colors )
 * 					   rotation from parent to DB node's direction
 * 					   still have DB, apply to new case
 * 				case : DB sibling is BLACK, far sibling's child from node is BLACK, near sibling RED
 * 					   swap colors between sibling and near sibling's child, then rotate sibling on opposite direction
 * 					   from DB node. Apply last case next ( black sibling, red far child ).
 * 			    case:  DB sibling is BLACK, and its far child is RED,
 * 					   swap color between sibling and parent, then rotate parent in DB node's direction, and lastly
 * 					   make sibling's far child node black.
 * 					   
 * 		   
 */

#include <utility>

namespace ft {

template< typename Key, typename Data >
class Node {

	private:
		Key		_key;
		Data	_data;
		
		Node*	leftChild;
		Node*	rightChild;
	public:
		
		Node( void );
		Node( Key key, Data data );
		Node( const Node& other );
		~Node( void );

		Node& operator=( const Node& other );

};

template< class Key, class Data >
class Tree {

	private:
		Node< Key, Data >*	root;

	public:

		Tree( void );
		Tree( Node< Key, Data >* root );
		Tree( const Tree& other );
		~Tree( void );

		Tree& operator=( const Tree& other );

		void insert( std::pair< Key, Data > data ) {

			// BST insertion

			// RBT case: recolor OR rotate OR rotate&&recolor

		}
		std::pair< Key, Data > search( Key key ) {

			// same as BST
		}
		void delete( Key key ) {

			// search for node

			// swap until leaf

			// RBT case: recolor and rotate until DB case is erased
		}
};

}

int main( void ) {

	ft::Tree< char, int > newTree;
	
	std::pair< char, int > data( 'a', 0 );

	newTree.insert( data );
	newTree.insert( );
	newTree.insert( );


}
