/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 19:20:07 by danrodri          #+#    #+#             */
/*   Updated: 2021/10/20 22:08:43 by danrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __STACK_HPP__
#define __STACK_HPP__
#include "vector.hpp"

namespace ft {

template< class T, class Container = ft::vector< T > >
class stack {
		
	public:
		typedef T			value_type;
		typedef Container	container_type;
		typedef size_t		size_type;

		explicit stack( const container_type& ctnr = container_type( ) ) : c( ctnr ) { }

		stack( const stack& other ) : c( other.c ) { }

		~stack( void ) { }

		/* assign */

		stack&	operator=( const stack& other ) {

			c = other.c;
		}

		/* top: calls to container back( ) func. to get reference to last element */
		value_type& top( void ) {

			return c.back( );
		}

		const value_type& top( void ) const {

			return c.back( );
		}

		/* empty: calls to container empty( ) func., returns true if empty */
		bool empty( void ) const {

			return c.empty( );
		}

		/* size: calls to container size( ) func., returns size */
		size_type size( void ) const {

			return c.size( );
		}

		/* push, pop: calls to container push_back( ) & pop_back( ) funcs. to add/remove elements */
		void push( const value_type& val ) {

			c.push_back( val );
		}

		void pop( void ) {

			c.pop_back( );
		}

		friend bool operator==( const stack& lhs, const stack& rhs ) {
		
			return lhs.c == rhs.c;
		}

		friend bool operator!=( const stack& lhs, const stack& rhs ) {
		
			return !( lhs == rhs );
		}

		friend bool operator<( const stack& lhs, const stack& rhs ) {
		
			return lhs.c < rhs.c;
		}

		friend bool operator<=( const stack& lhs, const stack& rhs ) {
		
			return !( lhs > rhs );
		}

		friend bool operator>( const stack& lhs, const stack& rhs ) {
		
			return ( rhs < lhs );
		}

		friend bool operator>=( const stack& lhs, const stack& rhs) {
		
			return !( lhs < rhs );
		}

	protected:
		container_type	c;

};

}

#endif
