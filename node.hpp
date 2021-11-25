/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 17:43:40 by danrodri          #+#    #+#             */
/*   Updated: 2021/11/18 18:51:51 by danrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __NODE_HPP__
#define __NODE_HPP__

#include <functional>
#include <iostream> // for test only

namespace ft {

enum { black, red } color_id;
enum { left, right } child_id;

template< class T,
		  class Compare = std::less< T >,
		  class Alloc = std::allocator< T > 
		>
class node {

	public:
		typedef T			 value_type;
		typedef Compare		 value_compare;
		typedef Alloc		 allocator_type;

		node* 		parent;
		node* 		child[2];

		node(	const value_type& value = value_type( ),
			  	const value_compare& comp = value_compare( ),
			  	const allocator_type& alloc = allocator_type( ) ) : 
			parent( ), 
			child( ), 
			node_comp( comp ),	
			node_value( value ), 
			node_color( red ),	
			node_alloc( alloc ) { 

		}

		node(	const node& other ) : 
			parent( ), 
			child( ), 
			node_comp( other.node_comp ),
			node_value( other.node_value ),
			node_color( other.color( ) ),
			node_alloc( other.node_alloc ) {

		}

		node& operator=( const node& other ) {

			if ( this == &other ) return *this;

			node_alloc = other.get_allocator( );
			node_alloc.destroy( &node_value );
			node_alloc.construct( &node_value, other.node_value );
			return *this;
		}

		~node( ) { 

			node_alloc.destroy( &node_value );
		}

		const int&	color( void ) const { 
			
			return node_color; 
		}
		void  		recolor( void ) { 
			
			node_color = !node_color; 
		}
        void  		recolor( int color ) { 
			
			node_color = color; 
		}

		allocator_type	get_allocator( void ) const { 
			
			return allocator_type( node_alloc );
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
		value_compare	node_comp;
		value_type		node_value;
		int				node_color;
		allocator_type	node_alloc;
};

}

#endif
