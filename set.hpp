/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 16:00:42 by danrodri          #+#    #+#             */
/*   Updated: 2021/11/23 17:47:44 by danrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SET_HPP__
#define __SET_HPP__
#include <functional>
#include <algorithm>
#include <memory>
#include "tree.hpp"
#include "reverse_iterator.hpp"

namespace ft {

template< class Key, class Compare = std::less< Key >, class Alloc = std::allocator< Key > >
class set {

    private:
        typedef ft::_tree< Key, Compare, Alloc >    set_tree;
        typedef typename set_tree::node                      set_node;
    public:
        typedef Key         key_type;
        typedef Key         value_type;
        typedef size_t      size_type;
        typedef ptrdiff_t   difference_type;
        typedef Compare     key_compare;
        typedef Compare     value_compare;
        typedef Alloc       allocator_type;

        typedef value_type&                      reference;
        typedef const value_type&                const_reference;
        typedef typename allocator_type::pointer          pointer;
        typedef typename allocator_type::const_pointer    const_pointer;

        typedef typename set_tree::iterator          iterator;
        typedef typename set_tree::const_iterator    const_iterator;

        typedef ft::reverse_iterator< iterator >        reverse_iterator;
        typedef ft::reverse_iterator< const_iterator >  const_reverse_iterator;

        set( const key_compare& comp = key_compare( ),
             const allocator_type& alloc = allocator_type( ) ) :
             
                _set_tree( comp ),
                _set_alloc( alloc ) {

        }

        template< class InputIterator >
        set( InputIterator first, InputIterator last,
             const key_compare& comp = key_compare( ),
             const allocator_type& alloc = allocator_type( ) ) :
             
                _set_tree( comp ),
                _set_alloc( alloc ) {

             for ( ; first != last; first++ ) {

                _set_tree.insert( *first );
             }
        }

        set( const set& other ) :
        
            _set_tree( other._set_tree ),
            _set_alloc( other._set_alloc ) {

        }

        ~set( ) { }

        set& operator=( const set& other ) {

            if ( this == &other ) return *this;
            _set_tree = other._set_tree;
            _set_alloc = other._set_alloc;
            return *this;
        }

        allocator_type getAllocator( void ) const {

            return allocator_type( );
        }

        iterator begin( void ) {

            return _set_tree.begin( );
        }

        const_iterator begin( void ) const {

            return _set_tree.begin( );
        }

        iterator end( void ) {

            return _set_tree.end( );
        }

        const_iterator end( void ) const {

            return _set_tree.end( );
        }

        reverse_iterator rbegin( void ) {

            return reverse_iterator( end( ) );
        }

        const_reverse_iterator rbegin( void ) const {

            return const_reverse_iterator( end( ) );
        }

        reverse_iterator rend( void ) {

            return reverse_iterator( begin( ) );
        }

        const_reverse_iterator rend( void ) const {

            return const_reverse_iterator( begin( ) );
        }

        bool empty( void ) const {

            return _set_tree.empty( );
        }

        size_type size( void ) const {

            return _set_tree.size( );
        }

        size_type max_size( void ) const {
        
            return _set_tree.max_size( );
        }

        void clear( void ) {

            _set_tree.clear( );
        }

        ft::pair< iterator, bool > insert( const value_type& val ) {

            return _set_tree.insert( val );
        }

        iterator insert( iterator hint, const value_type& val ) {

            return _set_tree.insert( hint, val );
        }

        template< class ItInput >
        void insert( ItInput first, ItInput last ) {

            for( ; first != last; first++ ) {

                _set_tree.insert( *first );
            }
        }

        void erase( iterator pos ) {

            _set_tree.erase( pos );
        }

        void erase( iterator first, iterator last ) {

            for( ; first != last; first++ ) {

                _set_tree.erase( first );
            }
        }

        size_type erase( const key_type& key ) {

            _set_tree.erase( key );
        }

        void swap( set& other ) {

            _set_tree.swap( other._set_tree );
        }

        size_type count( const key_type& key ) const {

            if ( !size( ) ) return 0;
            iterator    found_it = _set_tree.find( key );

            return ( *found_it == key ? 1 : 0 );
        }

        iterator find( const key_type& key ) {

            if ( !size( ) ) return end( );
            iterator    found_it = _set_tree.find( key );

            return ( *found_it == key ? found_it : end( ) );
        }

        const_iterator find( const key_type& key ) const {

            if ( !size( ) ) return end( );
            const_iterator    found_it = _set_tree.find( key );

            return ( *found_it == key ? found_it : end( ) );
        }

        ft::pair< iterator, iterator > equal_range( const key_type& key ) {

            iterator    first = lower_bound( key );
            iterator    second = upper_bound( key );

            return ft::make_pair< iterator, iterator >( first, second );
        }

        ft::pair< const_iterator, const_iterator > equal_range( const key_type& key ) const {

            const_iterator    first = lower_bound( key );
            const_iterator    second = upper_bound( key );

            return ft::make_pair< const_iterator, const_iterator >( first, second );
        }

        iterator lower_bound( const key_type& key ) {

            if ( !size( ) ) return 0;
            iterator	found_it = _set_tree.find( key );

			return  ( *found_it < key ) ? found_it++ : found_it;
        }

        const_iterator lower_bound( const key_type& key ) const {

            if ( !size( ) ) return 0;
            const_iterator	found_it = _set_tree.find( key );

			return  ( *found_it < key ) ? found_it++ : found_it;
        }

        iterator upper_bound( const key_type& key ) {

            if ( !size( ) ) return 0;
            iterator	found_it = _set_tree.find( key );

			return  ( *found_it <= key ) ? found_it++ : found_it;
        }

        const_iterator upper_bound( const key_type& key ) const {

            if ( !size( ) ) return 0;
            const_iterator	found_it = _set_tree.find( key );

			return  ( *found_it <= key ) ? found_it++ : found_it;
        }

        key_compare key_comp( void ) const {

            return key_compare( );
        }

        value_compare value_comp( void ) const {

            return value_compare( );
        }

        friend bool operator==( const ft::set< Key, Compare, Alloc >& lhs,
                                const ft::set< Key, Compare, Alloc >& rhs ) {

            return ( lhs._set_tree == rhs._set_tree );
        }

        friend bool operator!=( const ft::set< Key, Compare, Alloc >& lhs,
                                const ft::set< Key, Compare, Alloc >& rhs ) {

            return ( !( lhs == rhs ));
        }

        friend bool operator<( const ft::set< Key, Compare, Alloc >& lhs,
                               const ft::set< Key, Compare, Alloc >& rhs ) {

            return ( lhs._set_tree < rhs._set_tree );
        }

        friend bool operator>=( const ft::set< Key, Compare, Alloc >& lhs,
                                const ft::set< Key, Compare, Alloc >& rhs ) {

            return ( !( lhs < rhs ) );
        }

        friend bool operator>( const ft::set< Key, Compare, Alloc >& lhs,
                               const ft::set< Key, Compare, Alloc >& rhs ) {

            return ( rhs < lhs );
        }

        friend bool operator<=( const ft::set< Key, Compare, Alloc >& lhs,
                                const ft::set< Key, Compare, Alloc >& rhs ) {

            return ( !( rhs < lhs ) );
        }

    private:
        set_tree        _set_tree;
        allocator_type  _set_alloc;
};

template< class Key, class Compare, class Alloc >
void swap( ft::set< Key, Compare, Alloc >& lhs,
                ft::set< Key, Compare, Alloc >& rhs ) {

    lhs.swap( rhs );
}

}

#endif
