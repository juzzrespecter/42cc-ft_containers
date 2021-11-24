/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexicographical_compare.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 17:25:59 by danrodri          #+#    #+#             */
/*   Updated: 2021/10/19 20:12:57 by danrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* if range of vectors 1 has less elements than range of vectors 2, ( 1 < 2 ) and lexicographical_comp returns true */

#ifndef __LEXICOGRAPHICAL_COMPARE_HPP__
#define __LEXICOGRAPHICAL_COMPARE_HPP__

namespace ft {

template< class InputIterator1, class InputIterator2 >
bool lexicographical_compare( InputIterator1 first1, InputIterator1 last1,
							  InputIterator2 first2, InputIterator2 last2 ) {

	for( ; first1 != last1; first1++ ) {

		if ( first2 == last2 || *first2 < *first1 ) {

			return false;
		}
		if ( *first1 < *first2 ) {

			return true;
		}
		first2++;
	}

	return ( first2 != last2 );
}

template< class InputIterator1, class InputIterator2, class Compare >
bool lexicographical_compare( InputIterator1 first1, InputIterator1 last1,
							  InputIterator2 first2, InputIterator2 last2,
							  Compare compFunc ) {

	for( ; first1 != last1; first1++ ) {

		if ( first2 == last2 || !compFunc( *first1, *first2 ) ) {

			return false;
		}
		if ( compFunc( *first1, *first2 ) ) {

			return true;
		}
		first2++;
	}

	return ( first2 != last2 );
}

}

#endif
