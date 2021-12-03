#ifndef __PRINT_A_TREE_HPP__
#define __PRINT_A_TREE_HPP__

#include "map.hpp"
#include "vector.hpp"
#include <iostream>

#define RED_ "\033[31m"

template< class T >
void print_node( T n ) {
	std::cout << "< " << n << " >";
}

template< class T1, class T2 >
void print_node( ft::pair< T1, T2 > n ) {
	std::cout << "< " << n->first << " >";
}

template< class Node >
void print_recursion( Node* n, int lvl ) {

	if ( !n ) {
		std::cout << "<nil>";
		return ;
	}
	if( lvl ) std::cout << "-----";
	if( n->color( ) == ft::RED ) 
		std::cout << RED_; 
	print_node( *n ); std::cout << END;
	print_recursion( n->child[0], lvl + 1 );
	std::cout << "\n";
       	//indent( lvl );
	for( int i = 0; i < lvl; i++ ) std::cout << "          ";
	print_recursion( n->child[1], lvl + 1 );
}

template< class Tree >
void	print( Tree& tr ) {

	std::cout << "\n-------------------\n";
	print_recursion( tr.begin( ).root( ), 0 );
	std::cout << "-------------------\n";
}

#endif
