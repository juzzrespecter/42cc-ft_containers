#ifndef __ALGORITHM_HPP__
#define __ALGORITHM_HPP__

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