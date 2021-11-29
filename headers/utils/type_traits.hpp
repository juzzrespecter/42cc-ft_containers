/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 23:47:36 by danrodri          #+#    #+#             */
/*   Updated: 2021/11/29 23:47:36 by danrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __TYPE_TRAITS_HPP__
#define __TYPE_TRAITS_HPP__

namespace  ft {

template< bool B, class T = void >
	struct enable_if { };

template< class T >
	struct enable_if< true, T > { typedef T type; };


template< class T, T v >
struct integral_constant {

	public:
		typedef T								value_type;
		typedef integral_constant< T, v >	type;

		static const T value = v;

		operator value_type( ) const {

			return value;
		}
};

typedef	integral_constant< bool, true > true_type;
typedef	integral_constant< bool, false > false_type;

template< class T >
struct is_integral : public false_type { };

template< >
struct is_integral< bool > : public true_type { };

template< >
struct is_integral< char > : public true_type { };

template< >
struct is_integral< short int > : public true_type { };

template< >
struct is_integral< int > : public true_type { };

template< >
struct is_integral< long int > : public true_type { };

template< >
struct is_integral< long long int > : public true_type { };

template< >
struct is_integral< unsigned char > : public true_type { };

template< >
struct is_integral< unsigned short int > : public true_type { };

template< >
struct is_integral< unsigned int > : public true_type { };

template< >
struct is_integral< unsigned long int > : public true_type { };

template< >
struct is_integral< unsigned long long int > : public true_type { };


template< class T >
struct is_const : public false_type { };

template< class T >
struct is_const< const T > : public true_type { };

template< class T >
struct is_pointer : public false_type { };

template< class T >
struct is_pointer< T* > : public  true_type { };

template< class T >
struct is_pointer< T* const > : public true_type { };

}

#endif
