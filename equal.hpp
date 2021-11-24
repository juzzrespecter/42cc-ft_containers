/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 17:07:02 by danrodri          #+#    #+#             */
/*   Updated: 2021/10/19 20:23:49 by danrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __EQUAL_HPP__
#define __EQUAL_HPP__

namespace ft {

template< class InputIterator1, class InputIterator2 >
bool equal( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 ) {

	for ( ; first1 != last1; first1++ ) {

		if ( *first1 != *first2 ) {
			
			return false;
		}
		first2++;
	}

	return true;
}

template< class InputIterator1, class InputIterator2, class BinaryPredicate >
bool equal( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred ) {

	for ( ; first1 != last1; first1++ ) {

		if ( pred( *first1, *first2 ) == false ) {

			return false;
		}
		first2++;
	}

	return true;
}

}

#endif
