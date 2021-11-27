/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 18:10:41 by danrodri          #+#    #+#             */
/*   Updated: 2021/10/21 17:54:10 by danrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__
#include <limits>
#include <stdexcept>
#include <string>
#include "./utils/type_traits.hpp"
#include "./utils/iterator.hpp"
#include "./utils/algorithm.hpp"

/*	notes:
 *		size( ) vs. capacity( ) - size contains the number of stored elements, while capacity
 *			contains the number of elements that can be stored inside, meaning the current allocated
 *			memory on the array inside.
 *			When trying to *push_back( )* an element inside a vector overflowing its size,  vector
 *			will duplicate its capacity, then allocate that much memory into a new array and then 
 *			copy the old elements of the array into the new one. Finally, vector will destroy and deallocate
 *			all its elements, and the array will be replaced by the next one.
 *			[ push_back( ) checks size with *_vector_cap* attribute ]
 *
 * 			capacity is always initialized with *size* value.
 *
 * 		pop_back( ) - does NOT deallocate memory, but it makes call to object destructor.
 * 		clear( ) - same as pop_back, destroys and edits size, but does not deallocate memory.
 */

namespace ft {

template< class T >
class _vector_iterator {

	public:
		typedef std::random_access_iterator_tag	iterator_category;

		typedef typename ft::iterator_traits< T >::value_type		value_type;
		typedef typename ft::iterator_traits< T >::difference_type	difference_type;
		typedef typename ft::iterator_traits< T >::pointer			pointer;
		typedef typename ft::iterator_traits< T >::reference		reference;

		_vector_iterator( pointer ptr = NULL ) : _vector_ptr( ptr ), _offs( 0 ) { }

		_vector_iterator( const _vector_iterator& other ) : _vector_ptr( other.base( ) ), _offs( 0 ) { }

		/* copy constructor: iterator -> const_iterator, filters reverse conversion */
		template< class U >
		_vector_iterator( const _vector_iterator< U* >& other,
						  typename ft::enable_if< !ft::is_const< U >::value, U >::type* const_switch = NULL ) : 
			_vector_ptr( other.base( ) ), _offs( 0 ) { ( void )const_switch; }

		~_vector_iterator( void ) { }

		_vector_iterator& operator=( const _vector_iterator& other ) { 

			if ( this == &other ) return *this;

			_vector_ptr = other.base( );
			_offs = 0;
			return *this;
		}

		_vector_iterator& operator++( void ) { 

			_offs++;
			return *this;
		}

		_vector_iterator operator++( int ) {

			_vector_iterator _tmp( *this );
			_offs++;
			return _tmp;
		}

		_vector_iterator& operator--( void ) { 

			_offs--;
			return *this;
		}

		_vector_iterator operator--( int ) {

			_vector_iterator _tmp( *this );
			_offs--;
			return _tmp;
		}

		_vector_iterator operator+( difference_type n ) const {

			_vector_iterator _sum( *this );
			_sum._offs += n;
			return _sum;
		}

		_vector_iterator operator-( difference_type n ) const {

			_vector_iterator _sub( *this );
			_sub._offs -= n;
			return _sub;
		}

		_vector_iterator& operator+=( difference_type n ) {

			_offs += n;
			return *this;
		}
		_vector_iterator& operator-=( difference_type n ) {

			_offs -= n;
			return *this;
		}

		reference operator[]( difference_type i ) const {

			return _vector_ptr[ _offs + i ];
		}

		pointer operator->( void ) const {

			return _vector_ptr + _offs;
		}

		reference operator*( void ) const {

			return _vector_ptr[ _offs ];
		}

		pointer base( void ) const {

			return _vector_ptr + _offs;
		}

		friend _vector_iterator operator+( difference_type n, _vector_iterator it ) {

			_vector_iterator _sum( it );
			_sum._offs += n;
			return _sum;
		}

		friend _vector_iterator operator-( difference_type n, _vector_iterator it ) { 

			_vector_iterator _sub( it );
			_sub._offs -= n;
			return _sub;
		}

		template< class T1, class T2 >
		friend difference_type operator-( const _vector_iterator< T1 >& lhs, const _vector_iterator< T2 >& rhs ) {

			return( lhs._vector_ptr + lhs._offs ) - ( rhs._vector_ptr + rhs._offs );
		}

		template< class T1, class T2 >
		friend bool operator==( const _vector_iterator< T1 >& lhs, const _vector_iterator< T2 >& rhs ) { 

			return ( lhs._vector_ptr + lhs._offs ) == ( rhs._vector_ptr + rhs._offs ); 
		}

		template< class T1, class T2 >
		friend bool operator<( const _vector_iterator< T1 >& lhs, const _vector_iterator< T2 >& rhs ) {

			return ( lhs._vector_ptr + lhs._offs ) < ( rhs._vector_ptr + rhs._offs );
		}

		template< class T1, class T2 >
		friend bool operator!=( const _vector_iterator< T1 >& lhs, const _vector_iterator< T2 >& rhs ) { 

			return !( lhs == rhs ); 
		}

		template< class T1, class T2 >
		friend bool operator>( const _vector_iterator< T1 >& lhs, const _vector_iterator< T2 >& rhs ) {

			return ( rhs._vector_ptr + rhs._offs ) < ( lhs._vector_ptr + lhs._offs );
		}

		template< class T1, class T2 >
		friend bool operator>=( const _vector_iterator< T1 >& lhs, const _vector_iterator< T2 >& rhs ) { 

			return !( lhs < rhs ); 
		}

		template< class T1, class T2 >
		friend bool operator<=( const _vector_iterator< T1 >& lhs, const _vector_iterator< T2 >& rhs ) { 

			return !( lhs > rhs ); 
		}

	private:
		pointer 		_vector_ptr;
		difference_type _offs;

};

template< class T, class Alloc = std::allocator< T > >
class vector {

	public:

		typedef T	value_type;

		typedef std::allocator< T >			 				allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;

		typedef _vector_iterator< pointer >			iterator;
		typedef _vector_iterator< const_pointer >	const_iterator;

		typedef typename ft::reverse_iterator< iterator >					reverse_iterator;
		typedef typename ft::reverse_iterator< const_iterator >				const_reverse_iterator;
		typedef	typename ft::iterator_traits< iterator >::difference_type	difference_type;

		typedef size_t	size_type;

		/* default constructor: creates an empty vector ( mem. not allocated ) */
		explicit vector( const allocator_type& alloc = allocator_type( ) ) :
			_vector_arr( NULL ), _vector_size( 0 ),	_vector_cap( 0 ), _vector_alloc( alloc ) { }

		/* fill constructor: creates a sized *n* vector, elements initialized to val */
		explicit vector( size_type n, const value_type& val = value_type( ),
					     const allocator_type& alloc = allocator_type( ) ) :
			_vector_size( n ), _vector_cap( n ), _vector_alloc( alloc ) {

			_vector_arr = _vector_alloc.allocate( _vector_size );
			for ( size_type i = 0; i < _vector_size; i++ ) {

				_vector_alloc.construct( _vector_arr + i, val );
			}
		}

		/* range constructor: allocates & assigns as many elements as the range provided by iterators */
		template< class InputIterator >
			vector( InputIterator first, 
					typename ft::enable_if< !ft::is_integral< InputIterator >::value, InputIterator >::type last,
					const allocator_type& alloc = allocator_type( ) ) {

			_vector_alloc = alloc;
			_vector_size = last - first;
			_vector_cap = last - first;
			_vector_arr = _vector_alloc.allocate( _vector_size );
			for( size_type i = 0; first != last; first++, i++ ) {

				_vector_alloc.construct( _vector_arr + i, *first );
			}
		}

		/* copy constructor: deep copy of vector *other* */
		vector( const vector& other ) :
			_vector_arr( NULL ), _vector_alloc( other.get_allocator( ) ) {

			*this = other;
		}

		/* destructor: deallocates internal array */
		~vector( ) {

			_destroy_and_dealloc_array( );
		}

		/* assign operator */
		vector&	operator=( const vector& other ) {

			if ( this == &other )
				return *this;
			if ( _vector_arr != NULL ) {

				this->_destroy_and_dealloc_array( );
			}
			_vector_size = other.size( );
			_vector_cap = _vector_size;
			_vector_arr = _vector_alloc.allocate( _vector_size );
			for ( size_type i = 0; i < _vector_size; i++ ) {

				_vector_alloc.construct( _vector_arr + i, other[i] );
			}
			return *this;
		}

		/* begin: returns ptr constructor of iterator class, with ptr to first element */
		iterator begin( void ) {

			return iterator( _vector_arr );
		}

		const_iterator begin( void ) const {

			return const_iterator( _vector_arr );
		}

		/* end: returns ptr constructor of iterator class, with ptr to last element */
		iterator end( void ) {

			return iterator( _vector_arr + _vector_size );
		}

		const_iterator end( void ) const { 

			return const_iterator( _vector_arr + _vector_size );
		}

		/* rbegin: returns reverse_iterator built from iterator to last element */
		reverse_iterator rbegin( void ) {

			return ft::reverse_iterator< iterator >( end( ) );
		}

		const_reverse_iterator rbegin( void ) const {

			return ft::reverse_iterator< const_iterator >( end( ) );
		}

		/* rend: returns reverse_iterator built from iterator to prev. ptr to first element */
		reverse_iterator rend( void ) {

			return ft::reverse_iterator< iterator >( begin( ) );
		}

		const_reverse_iterator rend( void ) const {

			return ft::reverse_iterator< const_iterator >( begin( ) );
		}

		/* size: return private attribute _vector_size */
		size_type size( void ) const {

			return _vector_size;
		}

		/* max_size: returns max. n of elements that vector can hold ( = elements that alloc can allocate ) */
		size_type max_size( void ) const {

			return std::numeric_limits<difference_type>::max( );
		}

		/* resize: removes and destroys if n < _vector_size, constructs with copies of val if n > _vector_size
		 * 		   if n > _vector_cap, calls to reserve( ) */
		void resize( size_type n, value_type val = value_type( ) ) {

			if ( n > _vector_cap ) {

				size_type _new_vector_cap = ( n > _vector_cap * 2 ? n : _vector_cap * 2 );
				this->reserve( _new_vector_cap );
			}
			for ( size_type i = n; i < _vector_size; i++ ) _vector_alloc.destroy( &_vector_arr[i] );
			for ( size_type i = _vector_size; i < n; i++ ) _vector_alloc.construct( &_vector_arr[i], val );
			_vector_size = n;
		}

		/* size: return private attribute _vector_cap */
		size_type capacity( void ) const {

			return _vector_cap;
		}

		/* empty: returns true if size == 0, false if else */
		bool empty( void ) const {

			return !( _vector_size ) ? true : false;
		}

		/* reserve: reserves enough memory to contain n elements; only works if n > actual capacity of vector */
		void reserve( size_type n ) {

			if ( !n ) n++;
			if ( n > this->max_size( ) ) throw( std::length_error( what_length ) );
			if ( n <= _vector_cap ) return ;

			pointer _new_vector_arr;
			_new_vector_arr = _vector_alloc.allocate( n );
			for ( size_type i = 0; i < _vector_size; i++ ) {

				_vector_alloc.construct( &_new_vector_arr[i], _vector_arr[i] );
			}
			this->_destroy_and_dealloc_array( );
			_vector_arr = _new_vector_arr;
			_vector_cap = n;
		}

		/* []: returns ref. to element in index n of array, does not control out-of-bounds indexes */
		reference operator[]( size_type n ) {

			return _vector_arr[n];
		}

		const_reference operator[]( size_type n ) const {

			return _vector_arr[n];
		}

		/* at: array accesor like [], but throws exception at out-of-bounds indexes */
		reference at( size_type n ) {

			if ( n < 0 || n >= _vector_size ) throw( std::out_of_range( what_range ) );

			return _vector_arr[n];
		}

		const_reference at( size_type n ) const {

			if ( n < 0 || n >= _vector_size ) throw( std::out_of_range( what_range ) );

			return _vector_arr[n];
		}

		/* front: returns reference to first element */
		reference front( void ) {

			return _vector_arr[0];
		}

		const_reference front( void ) const {

			return _vector_arr[0];
		}

		/* back: returns ref. to last element (with index _vector_size - 1 ) */
		reference back( void ) {

			return _vector_arr[ _vector_size - 1 ];
		}

		const_reference back( void ) const {

			return _vector_arr[ _vector_size - 1 ];
		}

		/* assign: by range, replace with range provided by iterators */
		template< class InputIterator >
			void assign( InputIterator first, 
						 typename ft::enable_if< 
						 				!ft::is_integral< InputIterator >::value, 
										 InputIterator 
							>::type last ) {

				size_type _new_vector_size = last - first;

				for ( size_type i = 0; i < _vector_size; i++ ) {

					_vector_alloc.destroy( _vector_arr + i );
				}
				if ( _new_vector_size > _vector_cap ) {

					_vector_alloc.deallocate( _vector_arr, _vector_size );
					_vector_arr = _vector_alloc.allocate( _new_vector_size );
					_vector_cap = _new_vector_size;
				}
				_vector_size = _new_vector_size;
				for ( size_type i = 0; first != last; first++ ) {
					
					_vector_alloc.construct( _vector_arr + i, *first );
					i++;
				}
			}

		/* assign: fill, new vector witn n copies of val */
		void assign( size_type n, const value_type& val ) {

			for ( size_type i = 0; i < _vector_size; i++ ) {

				_vector_alloc.destroy( _vector_arr + i );
			}
			if ( n > _vector_cap ) {

				_vector_alloc.deallocate( _vector_arr, _vector_size );
				_vector_arr = _vector_alloc.allocate( n );
				_vector_cap = n;
			}
			_vector_size = n;
			for ( size_type i = 0; i < _vector_size; i++ ) {

				_vector_alloc.construct( _vector_arr + i, val );
			}
		}

		/* push_back: adds val to _vector_size array index.
		 * if push_back overflows, duplicate cap. size, allocate cap. to new array and copy, then destroy & dealloc old */
		void push_back( const value_type& val ) {

			if ( _vector_size == _vector_cap ) reserve( _vector_cap * 2 );

			_vector_alloc.construct( _vector_arr + _vector_size, val );
			_vector_size++;
		}

		/* pop_back: reduces size by one,  destroys last element of array */
		void pop_back( void ) {

			_vector_alloc.destroy( &_vector_arr[ _vector_size - 1 ] );
			_vector_size--;
		}

		/* insert: add element next to position indicated by iterator */
		iterator insert( iterator position, const value_type& val ) {

			size_type _offset = position - begin( );
			if ( _vector_size == _vector_cap ) this->reserve( _vector_cap * 2 );

			pointer _begin = _vector_arr + _offset;

			memmove( _begin + 1, _begin, sizeof( value_type ) * ( _vector_size - _offset ) );
			_vector_alloc.construct( _begin, val );
			_vector_size++;
			return position;
		}

		/* insert: fill *n* positions starting from iterator */
		void insert( iterator position, size_type n, const value_type& val ) {

			size_type _offset = position - begin( );
			if ( _vector_size + n > _vector_cap ) {

				this->_realloc_mem_to_array( n );
			}

			pointer _begin = _vector_arr + _offset;

			memmove( _begin + n, _begin, sizeof( value_type ) * ( _vector_size - _offset ) );
			for ( size_type i = 0; i < n; i++ )	{

				_vector_alloc.construct( _begin + i, val );
			}
			_vector_size += n;
		}

		/* insert: by range of iterators */
		template< class InputIterator >
			void insert( iterator position, InputIterator first, 
					     typename ft::enable_if< !ft::is_integral< InputIterator >::value, InputIterator >::type last ) {
			
				size_type _n_to_insert = last - first;
				size_type _offset = position - begin( );
				if ( _vector_size + _n_to_insert > _vector_cap ) {

					this->_realloc_mem_to_array( _n_to_insert );
				}

				pointer _begin = _vector_arr + _offset;

				memmove( _begin + _n_to_insert, _begin, sizeof( value_type ) * ( _vector_size - _offset ) );
				for( ; first != last; first++ ) {

					_vector_alloc.construct( _begin, *first );
					_begin++;
				}
				_vector_size += _n_to_insert;
		}

		/* erase: erase a single element indicated in iterator */
		iterator erase( iterator position ) {

			size_type _offset = position - begin( );
			pointer _begin = _vector_arr + _offset;

			_vector_alloc.destroy( _begin );
			if ( _offset + 1 < _vector_size ) {

				memmove( _begin, _begin + 1, sizeof( value_type ) * ( _vector_size - _offset ) );
			}
			_vector_size--;
			return position;
		}

		/* erase by range of iterators of the same vector */
		iterator erase( iterator first, iterator last ) {

			size_type _size_range = last - first;
			size_type _offset_first = first - begin( );
			size_type _offset_last = last - begin( );

			pointer _begin = _vector_arr + _offset_first;

			for ( ; first != last; first++ ) {

				_vector_alloc.destroy( _begin );
				_begin++;
			}
			if ( _offset_last + 1 < _vector_size )
				memmove( _vector_arr + _offset_first, _vector_arr + _offset_last, sizeof( value_type ) * _size_range ); 
			_vector_size -= _size_range;
			return ( _vector_arr + _offset_first );
		}

		/* swap: swaps arr & info between vectors. Previous ptrs, its & refs still usable */
		void swap( vector& other ) {

			pointer		_aux_arr = other._vector_arr;
			size_type	_aux_size = other._vector_size;
			size_type	_aux_cap = other._vector_cap;

			other._vector_arr = _vector_arr;
			other._vector_size = _vector_size;
			other._vector_cap = _vector_cap;

			_vector_arr = _aux_arr;
			_vector_size = _aux_size;
			_vector_cap = _aux_cap;
		}

		/* clear: destroys all elements, sets size to 0 */
		void clear( void ) {

			for ( size_type i = 0; i < _vector_size; i++ ) _vector_alloc.destroy( &_vector_arr[i] );
			_vector_size = 0;
		}

		/* allocator: returns copy of Alloc */
		allocator_type get_allocator( void ) const {

			return _vector_alloc;
		}

	private:
		pointer			_vector_arr;
		size_type		_vector_size;
		size_type		_vector_cap;

		allocator_type _vector_alloc;

		void	_destroy_and_dealloc_array( void ) {

			for ( size_type i = 0; i < _vector_size; i++ ) {

				_vector_alloc.destroy( &_vector_arr[i] );
			}
			_vector_alloc.deallocate( _vector_arr, _vector_size );
		}

		void	_realloc_mem_to_array( size_type _size_to_inc ) {

			size_type _new_cap = ( _vector_size + _size_to_inc > _vector_cap * 2 ) ?
				_vector_size + _size_to_inc :
				_vector_cap * 2;
			this->reserve( _new_cap );
		}

		static std::string what_length;
		static std::string what_range;

};

template < class T, class Alloc >
bool operator==( const vector< T, Alloc >& lhs, const vector< T, Alloc >& rhs ) {

	if ( lhs.size( ) != rhs.size( ) ) {

		return false;
	}

	return ft::equal( lhs.begin( ), lhs.end( ), rhs.begin( ) );
}

template< class T, class Alloc>
bool operator!=( const vector< T, Alloc >& lhs, const vector< T,Alloc >& rhs ) {

	return !( lhs == rhs );
}

template<class T, class Alloc>
bool operator<( const vector< T, Alloc >& lhs, const vector< T, Alloc >& rhs ) {

	return ft::lexicographical_compare( lhs.begin( ), lhs.end( ), rhs.begin( ), rhs.end( ) );
}

template<class T, class Alloc>
bool operator<=( const vector< T, Alloc >& lhs, const vector< T, Alloc >& rhs ) {

	return ( lhs < rhs || lhs == rhs ); 
}

template< class T, class Alloc >
bool operator>( const vector< T, Alloc >& lhs, const vector< T, Alloc >& rhs ) {

	return !( lhs <= rhs );
}

template< class T, class Alloc >
bool operator>=( const vector< T, Alloc >& lhs, const vector< T, Alloc >& rhs ) {

	return !( lhs < rhs );
}

/* overload of std::swap, simply uses swap method in vector class */
template< class T, class Alloc >
void swap( vector< T, Alloc >& x, vector< T, Alloc >& y ) {

	x.swap( y );
}

/* exception what( ) method strings */

template< class T, class Alloc >
std::string ft::vector< T, Alloc >::what_length = std::string( "allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size" );

template< class T, class Alloc >
std::string ft::vector< T, Alloc >::what_range = std::string( "vector" );

}

#endif
