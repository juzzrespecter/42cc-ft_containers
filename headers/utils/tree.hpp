/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:50:04 by danrodri          #+#    #+#             */
/*   Updated: 2021/11/24 20:23:46 by danrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __TREE_HPP__
#define __TREE_HPP__

#include "utility.hpp"
#include "iterator.hpp"
#include "algorithm.hpp"
#include "type_traits.hpp"

namespace ft {

enum { ERASE_FAIL, ERASE_SUCCESS } erase_ret_flags;
enum { BLACK, RED } color_id;
enum { LEFT, RIGHT } child_id;

template< class T,
		  class Compare = std::less< T >
		>
class node {

	public:
		typedef T			 value_type;
		typedef Compare		 value_compare;

		node* 		parent;
		node* 		child[2];

		node(	const value_type& value = value_type( ),
			  	const value_compare& comp = value_compare( ) ) : 
			parent( ), 
			child( ),
			node_value( value ), 
			node_comp( comp ),	
			node_color( RED ) { }

		node(	const node& other ) : 
			parent( ),
			child( ),
			node_value( other.node_value ),
			node_comp( other.node_comp ),
			node_color( other.color( ) ) { }

		node& operator=( const node& other ) {

			if ( this == &other ) return *this;

			node_value( other.node_value );
			return *this;
		}

		~node( ) { }

		const int&	color( void ) const { 
			
			return node_color; 
		}
		void  		recolor( void ) { 
			
			node_color = !node_color; 
		}
        void  		recolor( int color ) { 
			
			node_color = color; 
		}

		value_compare	value_comp( void ) const { 
			
			return node_comp; 
		}

		value_type&	operator* ( void ) { 
			
			return node_value;
		}

		friend bool operator==( const node& lhs, const node& rhs ) {

			return ( !( lhs < rhs ) && !( rhs < lhs ) );
		}

		friend bool operator!=( const node &lhs, const node &rhs ) {

			return ( !( lhs == rhs ) );
		}

		friend bool operator<( const node &lhs, const node &rhs ) {

			return ( lhs.value_comp( )( lhs.node_value, rhs.node_value ) );
		}

		friend bool operator>=( const node &lhs, const node &rhs ) {

			return ( !( lhs < rhs ) );
		}

		friend bool operator>( const node &lhs, const node &rhs ) {

			return ( lhs.value_comp( )( rhs.node_value, lhs.node_value ) );
		}

		friend bool operator<=( const node &lhs, const node &rhs ) {

			return ( !( lhs > rhs ) );
		}

	private:
		value_type		node_value;
		value_compare	node_comp;
		int				node_color;
};

template< class Node, class T >
class _tree_iterator {

	public:
		typedef std::bidirectional_iterator_tag	iterator_category;

		typedef typename ft::iterator_traits< T >::value_type		value_type;
		typedef typename ft::iterator_traits< T >::difference_type	difference_type;
		typedef typename ft::iterator_traits< T >::pointer			pointer;
		typedef typename ft::iterator_traits< T >::reference		reference;

		explicit _tree_iterator( Node* 	n_ptr = NULL, Node*	last_node = NULL ) :
			_n( n_ptr ), _last_node( last_node ) { }

		_tree_iterator( const _tree_iterator& other ) { 

			_n = other.base( );
			_last_node = other.get_last_node( );
		}

		template< class U >
		_tree_iterator( const _tree_iterator< Node, U* >& other, 
						typename ft::enable_if< !ft::is_const< U >::value, U >::type* const_switch = NULL ) {
 
			( void )const_switch;
			_n = other.base( );
			_last_node = other.get_last_node( );
		}
	
		~_tree_iterator( ) { }

		_tree_iterator&		operator=( const _tree_iterator& other ) {

			if ( this == &other ) return *this;
			_n = other._n;
			_last_node = other._last_node;
			return *this;
		}

		_tree_iterator&		operator++( void ) {

			if ( _n->child[ RIGHT ] ) {

				_n = _n->child[ RIGHT ];
				while ( _n->child[ LEFT ] ) _n = _n->child[ LEFT ];
				return *this;
			}
			while ( _n->parent ) {

				if ( *_n < *_n->parent ) break ;
				_n = _n->parent;
			}
			_n = _n->parent;
			return *this;
		}

		_tree_iterator		operator++( int ) {

			_tree_iterator tmp( *this );

			++( *this );
			return tmp;
		}

		_tree_iterator&		operator--( void ) {

			if ( _n == NULL ) {

				_n = _last_node->parent;
				while ( _n->child[ RIGHT ] ) _n = _n->child[ RIGHT ];
				return *this;
			}
			if ( _n->child[ LEFT ] ) {

				_n = _n->child[ LEFT ];
				while ( _n->child[ RIGHT ] ) _n = _n->child[ RIGHT ];
				return *this;
			}
			while ( *_n < *_n->parent ) {

				_n = _n->parent;
			}
			_n = _n->parent;
			return *this;
		}

		_tree_iterator		operator--( int ) {

			_tree_iterator tmp( *this );

			--( *this );
			return tmp;
		}

		reference	operator*( void ) const { return *( *_n ); }
		pointer		operator->( void ) const { return &( *( *_n ) ); }

		friend bool operator==( const _tree_iterator& lhs, const _tree_iterator& rhs ) {

			return ( lhs._n == rhs._n && 
					 lhs._last_node == rhs._last_node );
		}

		friend bool operator!=( const _tree_iterator& lhs, const _tree_iterator& rhs ) { return !( lhs == rhs ); }

		Node*	base( void ) const { return _n; }
		Node*	get_last_node( void ) const { return _last_node; }

	private:
		Node*		_n;
		Node*		_last_node;
};

template< class T,
		  class Compare = std::less< T >,
		  class Alloc = std::allocator< T >
		>
class _tree {

	public:
		typedef T			 value_type;
		typedef Compare      value_compare;
		typedef size_t       size_type;

		typedef ft::node< value_type, value_compare  >		node;
		typedef _tree_iterator< node, value_type* >			iterator;
		typedef _tree_iterator< node, const value_type* >	const_iterator;

		typedef typename Alloc::template rebind< node >::other				allocator_type;
		typedef typename ft::iterator_traits< iterator >::difference_type	difference_type;

		explicit _tree( const value_compare& comp = value_compare( ),
			            const allocator_type& alloc = allocator_type( ) ) : 
			_tree_root( ), _tree_size( ), _tree_comp( comp ), _tree_alloc( alloc ) { 

				_last_node = _tree_alloc.allocate( 1 );
			}

		_tree( const _tree& other ) :
			_tree_root( ), _tree_size( ), _tree_comp( other._tree_comp ), _tree_alloc( other._tree_alloc ) {

			_last_node = _tree_alloc.allocate( 1 );
			*this = other;
		}

		~_tree( ) {

			if ( _tree_root ) _delete_tree( _tree_root );
			_tree_alloc.deallocate( _last_node, 1 );
		}

		_tree& operator=( const _tree& other ) { 

			if ( this == &other ) return *this;
			if ( _tree_root != NULL ) {

				_delete_tree( _tree_root );
			}
			_tree_root = _copy_tree( other.root( ) );
			_last_node->parent = _tree_root;
			_tree_size = other.size( );
			return *this;
		}

		iterator begin( void ) {

			node*	_first = _tree_root;

			while ( _first && _first->child[ LEFT ] ) _first = _first->child[ LEFT ];
			return iterator( _first, _last_node );
		}

		const_iterator begin( void ) const {

			node*	_first = _tree_root;

			while ( _first && _first->child[ LEFT ] ) _first = _first->child[ LEFT ];
			return const_iterator( _first, _last_node );
		}

		iterator end( void ) {

			return iterator( NULL, _last_node );
		}

		const_iterator end( void ) const {

			return const_iterator( NULL, _last_node );
		}

		bool	empty( void ) const {

			return size( ) ? false : true;
		}

		size_type size( void ) const { 
			
			return _tree_size; 
		}

		size_type	max_size( void ) const {

			return std::min< size_type >( std::numeric_limits< difference_type >::max( ),
										  get_allocator( ).max_size( ) );
		}

		void	clear( void ) {

			_delete_tree( root( ) );
			_tree_root = NULL;
			_last_node->parent = NULL;
			_tree_size = 0;
		}

		ft::pair< iterator, bool >	insert( const value_type& value ) {

			iterator	hint_it = find( value );

			if ( hint_it == end( ) ) return ft::pair< iterator, bool >( _insert_root( value ), true );
			if ( !value_comp( )( *hint_it, value ) && 
				 !value_comp( )( value, *hint_it ) ) {
					 
				 return ft::pair< iterator, bool >( hint_it, false );
			}
			_tree_size++;
			node*	n = _new_node( hint_it.base( ), value );

			_insert_node_rb( n );
			return ft::pair< iterator, bool >( iterator( n, _last_node ), true );
		}

		/*
		 * tree insert hint optimizations:
		 *
		 * case 1 : empty tree - insert in root.
		 * case 2 : hint == end( ), if last element is less than value, insert in last pos. else insert std
		 * case 3 : hint with same key as value - do nothing, return.
		 * case 4 : hint == begin( ) && value less than first element, insert in first pos.
		 * case 4 : hint points to node comparing more than value,
		 *          hint's inorder predecessor points to node comparing lower than value,
		 * 			search for insert position from hint's pred ptr, then insert.
		 * 
		 * if insertion cannot be optimized, call insert( value ) overload.
		 */

		iterator	insert( const_iterator hint, const value_type& value ) {

			node*	n;

			if ( begin( ) == end( ) ) return _insert_root( value );
			if ( hint == end( ) ) {

				if ( value_comp( )( *( --end( ) ), value ) ) {

					n = _new_node( ( --end( ) ).base( ), value );
					_insert_node_rb( n );
					++_tree_size;
					return iterator( n, _last_node );
				}
				else return insert( value ).first;
			}
			if ( *hint == value ) return iterator( hint.base( ), hint.get_last_node( ) );
			if ( hint == begin( ) && value_comp( )( value, *hint ) ) {

				n = _new_node( ( begin( ) ).base( ), value );
				_insert_node_rb( n );
				++_tree_size;
				return iterator( n, _last_node );
			}
			if ( value_comp( )( value, *hint ) && value_comp( )( *( --hint ), value ) ) {

				n = _new_node( _find_in_subtree( hint.base( ), value ), value );
				_insert_node_rb( n );
				++_tree_size;
				return iterator( n, _last_node );
			}
			return insert( value ).first;
		}


		size_type	erase( const value_type& value ) { 

			iterator	it = find( value );

			if ( it == end( ) || value_comp( )( *it, value ) || value_comp( )( value, *it ) ) return ERASE_FAIL;
			erase( it );
			return ERASE_SUCCESS;
		}

		iterator	erase( const_iterator it ) {

			node*	_ptr = it.base( );
			node*	_nxt;

			_tree_size--;
			if ( _ptr == _tree_root && !_tree_size ) {

				_tree_alloc.destroy( _ptr );
				_tree_alloc.deallocate( _ptr, 1 );
				_tree_root = NULL;
				_last_node->parent = NULL;
				return end( );
			}

			_nxt = ( ++it ).base( );
			if ( is_inner_node( _ptr ) ) 
				_swap_nodes( _ptr, _nxt );
			_delete_node_cases( _ptr );
			_tree_alloc.destroy( _ptr );
			_tree_alloc.deallocate( _ptr, 1 );
			return iterator( _nxt, _last_node );
		}

		void	swap( _tree& other ) {

			enum aux_id { ROOT, LAST_NODE, SIZE };

			node*		_aux_n[ SIZE ] = { _tree_root, _last_node };
			size_type	_aux_size = _tree_size;

			_tree_root = other._tree_root;
			_last_node = other._last_node;
			_tree_size = other._tree_size;

			other._tree_root = _aux_n[ ROOT ];
			other._last_node = _aux_n[ LAST_NODE ];
			other._tree_size = _aux_size;
		}

		iterator find( const value_type& value ) {

			node	*n = _find_in_subtree( _tree_root, value );
			return iterator( n, _last_node );
		}

		const_iterator find( const value_type& value ) const {

			node	*n = _find_in_subtree( _tree_root, value );
			return const_iterator( n, _last_node );
		}

		node* root( void ) const { 
			
			return _tree_root; 
		}

		value_compare	value_comp( void ) const {

			return _tree_comp;
		}

		allocator_type	get_allocator( void ) const { 
			
			return _tree_alloc;
		}

	private:
		node*       		_tree_root;
		node*				_last_node;
		size_type			_tree_size;
		value_compare		_tree_comp;
		allocator_type		_tree_alloc;

		typedef	void ( _tree::*rb_cases )( node* n );

		/************************************ ROTATE ************************************/

		void rotate( node* old_root, int dir ) {

			node* new_root = old_root->child[ !dir ];
            
			if ( !new_root ) return ;
			if ( old_root == root( ) ) {

				_tree_root = new_root;
				_last_node->parent = _tree_root;
			} else {

				old_root->parent->child[ whoami( old_root ) ] = new_root;
			}
			new_root->parent = old_root->parent;
			old_root->parent = new_root;

			old_root->child[ !dir ] = new_root->child[ dir ];
			new_root->child[ dir ] = old_root;

			if ( old_root->child[ !dir ] != NULL ) {

				old_root->child[ !dir ]->parent = old_root;
			}
		}
		/* ******************************************************************************* */






		/* **************************** FIND NODE FUNCTIONS ****************************** */

		node*	_find_in_subtree( node* _n, const value_type& value ) const {

			if ( !_n ) return NULL;
			node*	_next_n;

			while ( value_comp( )( *( *_n ), value ) || 
				    value_comp( )( value, *( *_n ) ) ) {

				if ( value_comp( )( *( *_n ), value ) ) {
					_next_n = _n->child[ RIGHT ];
				} else {
					_next_n = _n->child[ LEFT ];
				}

				if ( !_next_n ) break ;
				_n = _next_n;
			}
			return _n;
		}
		/* ******************************************************************************** */






		/* *************************** DELETE NODE FUNCTIONS ***************************** */

		/* 
		 * ( we are working here with non-inner nodes here )
		 *
		 * case 1: node to delete is RED, make parent's access to node NULL
		 * case 2: node to delete is BLACK and has a RED child ( RED means non-leaf, and other child is leaf ),
		 * 		   recolor child and remove node ( rewrite parent and child's access )
		 * case 3: check recursive cases 
		 * 
		 */

		void	_delete_node_cases( node* node_ptr ) {

			rb_cases _delete_node_cases_table[2] = {

				&_tree::_delete_node_case_1,
				&_tree::_delete_node_case_2
			};

			int	id_child = node_ptr->child[ RIGHT ] ? RIGHT : LEFT;
			int	id_case = !( node_ptr->color( ) == RED );

			if ( id_case ) id_case += !( is_color( node_ptr->child[ id_child ] ) );
			if ( id_case == 1 ) node_ptr = node_ptr->child[ id_child ];

			if ( id_case == 2 ) {
				
				_delete_node_rb_cases( node_ptr );
				if ( node_ptr->parent ) node_ptr->parent->child[ whoami( node_ptr ) ] = NULL;
			}
			else ( this->*_delete_node_cases_table[ id_case ] )( node_ptr );
		}

		/* 
		 * delete recursive balance cases:
		 *  	n -> node
		 * 		P( n ) -> parent of node
		 * 		G( n ) -> grandparent of node
		 * 		S( n ) -> sibling of node
		 * 		N( n ) -> nearest child of sibling to node
		 * 		F( n ) -> furthest child of sibling to node
		 * 
		 * 
		 * 		case 1: S( n ) is RED,
		 * 				swap S and P's colors,
		 * 				rotate P in node's direction,
		 * 				then check next case on same node.
		 * 		case 2: S( n ) is BLACK, F( n ) is RED,
		 * 				swap S and P's colors,
		 * 				recolor F BLACK,
		 * 				rotate P to node's direction.
		 * 		case 3: S( n ) is BLACK, F( n ) is BLACK, N( n ) is RED,
		 * 				swap N and S's colors,
		 * 				rotate S in opposite direction to node,
		 * 				then call case 4.
		 * 		case 4: S's entire subtree { S, F, N } is BLACK,
		 * 				recolor S RED,
		 * 				recolor P BLACK,
		 * 				check next case in P only if P was already BLACK.
		 * 
		 * 	src = https://medium.com/analytics-vidhya/deletion-in-RED-BLACK-rb-tree-92301e1474ea
		 */

		void _delete_node_rb_cases( node* n ) {

			if ( n == root( ) ) {

				n->recolor( BLACK );
				return ;
			}

			rb_cases _delete_node_rb_cases_table[4] = {

				&_tree::_delete_node_rb_case_1,
				&_tree::_delete_node_rb_case_2,
				&_tree::_delete_node_rb_case_3,
				&_tree::_delete_node_rb_case_4
			};

			int	case_id = ( is_color( sibling_of( n ) ) == BLACK );
			if ( case_id && is_color( far_child_of( n ) ) == BLACK ) {

				case_id += ( is_color( near_child_of( n ) ) == RED ) ? 1 : 2;
			}

			( this->*_delete_node_rb_cases_table[ case_id ] )( n );
		}

		void	_delete_node_case_1( node* n ) { 

			n->parent->child[ whoami( n ) ] = NULL;
		}

		void	_delete_node_case_2( node* child ) { 

			node*	n = child->parent;

			child->recolor( );
			child->parent = n->parent;

			if ( n == root( ) ) {

				_tree_root = child;
				_last_node->parent = _tree_root;
			} else {

				n->parent->child[ whoami( n ) ] = child;
			}
			child->parent = n->parent;
		}

		void	_delete_node_rb_case_1( node* n ) {

			sibling_of( n )->recolor( n->parent->color( ) );
			n->parent->recolor( RED );
			rotate( n->parent, whoami( n ) );
			_delete_node_rb_cases( n );
		}

		void	_delete_node_rb_case_2( node* n ) {

			sibling_of( n )->recolor( n->parent->color( ) );
			n->parent->recolor( BLACK );
			far_child_of( n )->recolor( BLACK );
			rotate( n->parent, whoami( n ) );
		}

		void	_delete_node_rb_case_3( node* n ) {

			near_child_of( n )->recolor( BLACK );
			sibling_of( n )->recolor( RED );
			rotate( sibling_of( n ), !whoami( n ) );
			_delete_node_rb_case_2( n );
		}

		void	_delete_node_rb_case_4( node* n ) {

			sibling_of( n )->recolor( RED );
			if ( n->parent->color( ) == BLACK ) {
				
				_delete_node_rb_cases( n->parent );
			} else {
				
				n->parent->recolor( );
			}
			return ;
		}

		/* if something goes wrong blame this little pos */
		void	_swap_nodes( node* _n1, node* _n2 ) {
			
			int		_n1_color = _n1->color( );
			_n1->recolor( _n2->color( ) );
			_n2->recolor( _n1_color );

			node*	_aux_n[3] = { _n1->parent, _n1->child[ LEFT ], _n1->child[ RIGHT ] };
			int	_n_id[2] = { 
					( _n1->parent ) ? whoami( _n1 ) : -1,
			       	( _n2->parent ) ? whoami( _n2 ) : -1 
			};

			_n1->parent = ( _n2->parent == _n1 ) ? _n2 : _n2->parent;
			_n1->child[ LEFT ] = _n2->child[ LEFT ];
			_n1->child[ RIGHT ] = _n2->child[ RIGHT ];

			_n2->parent = _aux_n[0];
			_n2->child[ LEFT ] = ( _aux_n[1] == _n2 ) ? _n1 : _aux_n[1];
			_n2->child[ RIGHT ] = ( _aux_n[2] == _n2 ) ? _n1 : _aux_n[2];

			if ( _n1->parent ) _n1->parent->child[ _n_id[1] ] = _n1;
			if ( _n1->child[ LEFT ] ) _n1->child[ LEFT ]->parent = _n1;
			if ( _n1->child[ RIGHT ] ) _n1->child[ RIGHT ]->parent = _n1;

			if ( _n2->parent ) _n2->parent->child[ _n_id[0] ] = _n2;
			if ( _n2->child[ LEFT ] ) _n2->child[ LEFT ]->parent = _n2;
			if ( _n2->child[ RIGHT ] ) _n2->child[ RIGHT ]->parent = _n2;

			if ( _n1 == root( ) ) {
				
				_tree_root = _n2;
				_last_node->parent = _n2;
			}
		}

		/********************************************************************************/




		/**************************** INSERT NODE FUNCTIONS ******************************/

		iterator	_insert_root( const value_type& value ) {

			node	node_value( value, _tree_comp );

			_tree_root = _tree_alloc.allocate( 1 );
			_tree_alloc.construct( _tree_root, node_value );
			_last_node->parent = _tree_root;
			_tree_root->recolor( );
			_tree_size++;
			return	iterator( _tree_root, _last_node );
		}

		node*	_new_node( node* _parent_n, const value_type& value ) {

			node*	_new_n = _tree_alloc.allocate( 1 );
			node	_aux_n( value, _tree_comp );

			_tree_alloc.construct( _new_n, _aux_n );
			_new_n->parent = _parent_n;
			_parent_n->child[ ( *_new_n < *_parent_n ) ? LEFT : RIGHT ] = _new_n;
			return _new_n;
		}

		/* 
		 * insert cases:
		 *		n -> node
		 *		P( n ) -> parent of node
		 *		U( n ) -> uncle of node
		 *		G( n ) -> grandparent of node
		 *
		 * 		case 1: node is root, change color from RED to BLACK
		 *		case 2: P( n ) is BLACK, tree is balanced, nothing to do
		 *		case 3: P( n ) and U( n ) are RED,
		 *				repaint them, 
		 *				repaint G( n ) if G != root,
		 *				recursive call in G( n ) to check if tree is balanced
		 *		case 4: P( n ) is RED, U( n ) is BLACK, and n and P( n ) do not share same child id,
		 *				rotate P in opposite direction, then call case 5 with old P( n )
		 *		case 5: P( n ) is RED, U( n ) is BLACK, n and P( n ) do share same child id,
		 *				rotate G( n ) in opposite direction,
		 *				recolor P and G
		 *
		 * 	src = https://cs.kangwon.ac.kr/~leeck/file_processing/red_black_tree.pdf
		 */

		void _insert_node_rb( node* n ) {

			rb_cases _insert_node_cases[3] = {

				&_tree::_insert_node_rb_case_3,
				&_tree::_insert_node_rb_case_4,
				&_tree::_insert_node_rb_case_5
			};

			if ( n == _tree_root ) { /* Case 1 */

				n->recolor( BLACK );
				return ;
			} 
			if ( n->parent->color( ) == BLACK ) { /* Case 2 */
				
				return ;
			}

			int case_id = ( is_color( uncle_of( n ) ) == BLACK );
			if ( case_id ) {

				case_id += ( whoami( n ) == whoami( n->parent ) );
			}
			( this->*_insert_node_cases[ case_id ] )( n );
		}

		void _insert_node_rb_case_3( node* n ) {

			parent_of( n )->recolor( );
			uncle_of( n )->recolor( );
			if ( grandparent_of( n ) != root( ) ) {
				
				grandparent_of( n )->recolor( );
			}
			_insert_node_rb( grandparent_of( n ) );
		}

		void _insert_node_rb_case_4( node* n ) {

			node* aux = n->parent;

			rotate( n->parent, whoami( n->parent ) );
			_insert_node_rb( aux );
		}

		void _insert_node_rb_case_5( node* n ) {

			parent_of( n )->recolor( );
			grandparent_of( n )->recolor( );
			rotate( grandparent_of( n ), !whoami( n ) );
		}

		/********************************************************************************/






		/******************************* NODE OPERATORS *********************************/

		int whoami( node* me ) const { return ( me->parent->child[ LEFT ] == me ) ? LEFT : RIGHT; }

		bool is_inner_node( node* n ) const { return ( n->child[ RIGHT ] && n->child[ LEFT ] ); }

		node* parent_of( node* node ) const { return node->parent; }

		node* grandparent_of( node* node ) const { return ( parent_of( node->parent ) ); }

		node* uncle_of( node* node ) const { return ( grandparent_of( node )->child[ !whoami( node->parent ) ] ); }

		node* sibling_of( node* node ) const { return ( parent_of( node )->child[ !whoami( node ) ] ); }

		node* near_child_of( node* node ) const { return ( sibling_of( node )->child[ whoami( node ) ] ); }

		node* far_child_of( node* node ) const { return ( sibling_of( node )->child[ !whoami( node ) ] ); }

		int	 is_color( node* node_to_check ) const {

			if ( !node_to_check || node_to_check->color( ) == BLACK ) return BLACK;
			return ( RED );
		}

		/********************************************************************************/





		/******************************* TREE TRAVERSALS *********************************/

		node* _copy_tree( node* n_cpy ) {

			if ( !n_cpy ) return NULL;

			node* _new_n = _tree_alloc.allocate( 1 );
			_tree_alloc.construct( _new_n, *n_cpy );

			_new_n->child[ LEFT ] = _copy_tree( n_cpy->child[ LEFT ] );
			if ( _new_n->child[ LEFT ] ) _new_n->child[ LEFT ]->parent = _new_n;

			_new_n->child[ RIGHT ] = _copy_tree( n_cpy->child[ RIGHT ] );
			if ( _new_n->child[ RIGHT ] ) _new_n->child[ RIGHT ]->parent = _new_n;
			return _new_n;
		}

		void _delete_tree( node* n_del ) {

			if ( !n_del ) return ;
			
			_delete_tree( n_del->child[ LEFT ] );
			_delete_tree( n_del->child[ RIGHT ] );

			_tree_alloc.destroy( n_del );
			_tree_alloc.deallocate( n_del, 1 );
		}

		/********************************************************************************/
};

template< class T, class Compare, class Alloc >
bool operator==( const ft::_tree< T, Compare, Alloc >& lhs,
                 const ft::_tree< T, Compare, Alloc >& rhs ) {

	if ( lhs.size( ) != rhs.size( ) ) return false;

	return ft::equal( lhs.begin( ), lhs.end( ), rhs.begin( ) );
}

template< class T, class Compare, class Alloc >
bool operator!=( const ft::_tree< T, Compare, Alloc >& lhs,
                 const ft::_tree< T, Compare, Alloc >& rhs ) {

	return ( !( lhs == rhs ) );
}
template< class T, class Compare, class Alloc >
bool operator<( const ft::_tree< T, Compare, Alloc >& lhs,
                const ft::_tree< T, Compare, Alloc >& rhs ) {

	return ft::lexicographical_compare( lhs.begin( ), lhs.end( ), rhs.begin( ), rhs.end( ) );
}

template< class T, class Compare, class Alloc >
bool operator<=( const ft::_tree< T, Compare, Alloc >& lhs,
                 const ft::_tree< T, Compare, Alloc >& rhs ) {

	return ( lhs == rhs || lhs < rhs );
}

template< class T, class Compare, class Alloc >
bool operator>( const ft::_tree< T, Compare, Alloc >& lhs,
                const ft::_tree< T, Compare, Alloc >& rhs ) {

	return ( rhs < lhs );
}

template< class T, class Compare, class Alloc >
bool operator>=( const ft::_tree< T, Compare, Alloc >& lhs,
                 const ft::_tree< T, Compare, Alloc >& rhs ) {

	return ( lhs > rhs || lhs == rhs );
}

}

#endif
