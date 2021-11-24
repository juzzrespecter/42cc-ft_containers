/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 21:28:26 by danrodri          #+#    #+#             */
/*   Updated: 2021/10/18 21:44:59 by danrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __PAIR_HPP__
#define __PAIR_HPP__
#include "enable_if.hpp"
#include "is_integral.hpp"

namespace ft {

template< class T1, class T2 >
struct pair {

    public:
        T1 first;
        T2 second;

        pair( void ) : first( T1( ) ), second( T2( ) ) { }

        template< class U1, class U2 >
        pair( const pair< U1, U2 >& other ) : first( other.first ), second( other.second ) { }

        pair( const T1& x, const T2& y ) : first( x ), second( y ) { }

        ~pair( ) { }

        pair& operator= ( const pair< T1, T2 >& other ) {

            if ( this == &other ) return *this;
            first = other.first;
            second = other.second;
            return *this;
        }
};

template< class T1, class T2 >
bool operator==( const ft::pair< T1, T2 >& lhs, const ft::pair< T1, T2 >& rhs ) {

    return ( lhs.first == rhs.first && lhs.second == rhs.second );
}

template< class T1, class T2 >
bool operator!=( const ft::pair< T1, T2 >& lhs, const ft::pair< T1, T2 >& rhs ) {

    return !( lhs == rhs );
}
template< class T1, class T2 >
bool operator<( const ft::pair< T1, T2 >& lhs, const ft::pair< T1, T2 >& rhs ) {

    if ( lhs.first > rhs.first ) return false;
    if ( lhs.first < rhs.first ) return true;
    return ( lhs.second < rhs.second );
}
template< class T1, class T2 >
bool operator<=( const ft::pair< T1, T2 >& lhs, const ft::pair< T1, T2 >& rhs ) {

    return ( lhs < rhs || lhs == rhs );
}
template< class T1, class T2 >
bool operator>( const ft::pair< T1, T2 >& lhs, const ft::pair< T1, T2 >& rhs ) {

    return !( lhs <= rhs );
}
template< class T1, class T2 >
bool operator>=( const ft::pair< T1, T2 >& lhs, const ft::pair< T1, T2 >& rhs ) {

    return !( lhs < rhs );
}

template< class T1, class T2 >
ft::pair< T1, T2 > make_pair( T1 x, T2 y ) {

    return ft::pair< T1, T2 >( x, y );
}

}

#endif
