#ifndef __ITERATOR_HPP__
#define __ITERATOR_HPP__

#include <iterator> // for the iterator tags
#include <cstddef> // for ptrdiff_t definition

namespace ft {

/* takes defined typedefs of Iterator */
template< class Iterator >
class iterator_traits {

	public:
		typedef typename Iterator::difference_type	difference_type;
		typedef typename Iterator::value_type	  	value_type;
		typedef typename Iterator::pointer			pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;

};

/* provides typedefs to pointers as iterators */
template< class T >
class iterator_traits< T* > {

	public:
		typedef std::ptrdiff_t					difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef std::random_access_iterator_tag	iterator_category;

};

/* same as above specialization, for const pointers */
template< class T >
class iterator_traits< const T* > {

	public:
		typedef std::ptrdiff_t					difference_type;
		typedef T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef std::random_access_iterator_tag	iterator_category;

};

/* iterator wrapper, reverses increment / decrement calls */
template< class Iterator >
class reverse_iterator {

	public:
		typedef Iterator iterator_type;

		typedef typename ft::iterator_traits< Iterator >::iterator_category	iterator_category;
		typedef typename ft::iterator_traits< Iterator >::value_type		vallue_type;
		typedef typename ft::iterator_traits< Iterator >::difference_type	difference_type;
		typedef typename ft::iterator_traits< Iterator >::pointer			pointer;
		typedef typename ft::iterator_traits< Iterator >::reference			reference;

		reverse_iterator( void ) : _current_it( NULL ) { }

		explicit reverse_iterator( iterator_type it ) : _current_it( it ) { }

		template< class It >
		reverse_iterator ( const reverse_iterator< It >& other ) : _current_it( other.base( ) ) { }

		~reverse_iterator( void ) { }

		template< class It >		
		reverse_iterator& operator=( const reverse_iterator< It >& other ) {

			if ( this == &other ) return *this;

			_current_it = other.base( );
			return *this;
		}

		iterator_type base( void ) const {

			return _current_it;
		}

		reference operator*( void ) const {

			iterator_type	tmp( _current_it );
			return *( --tmp );
		}

		pointer operator->( void ) const {

			return &( operator*( ) );
		}

		reference operator[] ( difference_type n ) const {

			return _current_it[ - n - 1 ];
		}

		reverse_iterator& operator++( void ) {

			--_current_it;
			return *this;
		}

		reverse_iterator operator++( int ) {

			reverse_iterator _tmp( *this );
			--_current_it;
			return _tmp;
		}

		reverse_iterator& operator--( void ) {

			++_current_it;
			return *this;
		}

		reverse_iterator operator--( int ) {

			reverse_iterator _tmp( *this );
			++_current_it;
			return _tmp;
		}

		reverse_iterator operator+( difference_type n ) {

			reverse_iterator _tmp( *this );
			_tmp += n;
			return _tmp;
		}

		reverse_iterator operator-( difference_type n ) {

			reverse_iterator _tmp( *this );
			_tmp -= n;
			return _tmp;
		}

		reverse_iterator& operator+=( difference_type n ) {

			_current_it -= n;
			return *this;
		}

		reverse_iterator& operator-=( difference_type n ) {

			_current_it += n;
			return *this;
		}

		friend bool operator==( const reverse_iterator& lhs, const reverse_iterator& rhs ) {

			return ( lhs.base( ) == rhs.base( ) );
		}

		friend bool operator!=( const reverse_iterator& lhs, const reverse_iterator& rhs ) {

			return ( lhs.base( ) != rhs.base( ) );
		}

		friend bool operator<( const reverse_iterator& lhs, const reverse_iterator& rhs ) {

			return ( lhs.base( ) < rhs.base( ) );
		}

		friend bool operator>( const reverse_iterator& lhs, const reverse_iterator& rhs ) {

			return ( lhs.base( ) > rhs.base( ) );
		}


		friend bool operator<=( const reverse_iterator& lhs, const reverse_iterator& rhs ) {

			return ( lhs.base( ) <= rhs.base( ) );
		}

		friend bool operator>=( const reverse_iterator& lhs, const reverse_iterator& rhs ) {

			return ( lhs.base( ) >= rhs.base( ) );
		}

		friend reverse_iterator operator+( difference_type n, const reverse_iterator& it ) {

			reverse_iterator _tmp( it );

			_tmp += n;
			return _tmp;
		}

		friend difference_type operator-( const reverse_iterator& lhs, const reverse_iterator& rhs ) {

			return lhs.base( ) - rhs.base( );
		}

	protected:
		iterator_type _current_it;

};

}

#endif