/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 14:40:23 by danrodri          #+#    #+#             */
/*   Updated: 2021/10/19 20:27:22 by danrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
 * notes about iterators:
 * 		base class std::iterator:
 * 			template<
 * 				class Category,	----> must be an iterator_category_tag
 * 				class T,
 * 				class Distance = std::ptrdiff_t,
 * 				class Pointer = T*,
 *				class Reference = T&
 *			> struct iterator;
 *
 * 		STL requires that every iterator class provides a type called *iterator_category* or tag,
 * 		and several typedefs: 
 * 								.value_type( value of element pointed to ), 
 * 								.difference_type( type resulting from a difference [ - ] of two iterators ), 
 * 								.pointer( type pointer to the element ), 
 * 								.reference( type ref. that iterator refers to ).
 *
 *		(std::)iterator_tags: { output, input, forward, bidirectional, random access }
 *							  We will use random_access tag for these containers.
 *
 * 		iterator_traits: template that exposes these 5 defined types. If the template type passed to iterator_traits
 * 		is not a pointer, it forwards the types from the iterator itself - iterator_traits<it>::value_type -> it::value_type.
 * 		If it is a pointer: iterator_traits<T*>::value_type is hardcoded T, iterator_traits<T*>::iterator_category is 
 * 		hardcoded random_access_iterator_tag.
 *
 * 		std::iterator: as a public class inherited from by custom iterator, builds these required types
 *
 * 		random access iterator: must satisfy
 * 			value_type, as ft::iterator_traits<Iterator>::value_type
 * 			difference_type, as ft::iterator_traits<Iterator>::difference_type
 * 			reference, as ft::iterator_traits<Iterator>::reference
 *
 * 			constructibe, copy-constructible, copy-assignable, destructible, swappable
 *
 * 			+= / -= overload with difference_type { implemented not as a loop, complexity is constant }
 * 			+ / - overload with difference_type 
 * 			- overload with iterator
 * 			[] overload { *( it + num ) }
 * 			< / > /  <= / >= overload
 *
 * 			++, *++, --, *--, !=, *, (void)++
 * 			( a == b -> a++ == b++ )
 */

#ifndef __ITERATOR_TRAITS_HPP__
#define __ITERATOR_TRAITS_HPP__

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

}

#endif
