/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 19:18:47 by danrodri          #+#    #+#             */
/*   Updated: 2021/10/21 16:48:30 by danrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* template magic: specifiers create *true* is_integral, *false* for general case 
 * 	{ integral types in c++98: bool, char, short int, int, long int, long long int,
 * 							   unsigned char, unsigned short int, unsigned int, unsigned long int, 
 * 							   unsigned long long int }
 */

#ifndef __IS_INTEGRAL_HPP__
#define __IS_INTEGRAL_HPP__

namespace ft {

template< class T, T v >
struct integral_constant {

	public:
		typedef T								value_type;
		typedef ft::integral_constant< T, v >	type;

		static const T value = v;

		operator value_type( ) const {

			return value;
		}
};

typedef	ft::integral_constant< bool, true > true_type;
typedef	ft::integral_constant< bool, false > false_type;

template< class T >
struct is_integral : public ft::false_type { };

template< >
struct is_integral< bool > : public ft::true_type { };

template< >
struct is_integral< char > : public ft::true_type { };

template< >
struct is_integral< short int > : public ft::true_type { };

template< >
struct is_integral< int > : public ft::true_type { };

template< >
struct is_integral< long int > : public ft::true_type { };

template< >
struct is_integral< long long int > : public ft::true_type { };

template< >
struct is_integral< unsigned char > : public ft::true_type { };

template< >
struct is_integral< unsigned short int > : public ft::true_type { };

template< >
struct is_integral< unsigned int > : public ft::true_type { };

template< >
struct is_integral< unsigned long int > : public ft::true_type { };

template< >
struct is_integral< unsigned long long int > : public ft::true_type { };


template< class T >
struct is_const : public ft::false_type { };

template< class T >
struct is_const< const T > : public ft::true_type { };

}

#endif
