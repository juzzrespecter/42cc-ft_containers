#ifndef __TESTER_HPP__
#define __TESTER_HPP__

#include <sys/time.h>
#include <string>
#include <iostream>
#include <cstdlib>

#define	CYAN	"\033[33m"
#define	END	"\033[0m"

#define OK	"\033[32m [ OK ] \033[0m"	
#define KO	"\033[31m [ KO ] \033[0m"
#define ID( x )	CYAN<<"[ "<<x<<" ]"<<END

#define N_TEST 4

#define N_VECTOR_TEST	22
#define N_STACK_TEST	8 // maybe
#define N_MAP_TEST	20
#define N_SET_TEST	18 // maybe

template< class Node >
void	print_tree( Node n, int lvl ) {

	if ( !n ) {

		std::cout << "<nil>";
		return ;
	}
	print_node( n );
	print_tree( n->child[ 0 ] );
	std::cout << "\n"; indent( lvl );
	print_tree( n->child[ 1 ] );
}

void	vector_tests( void );
void	map_tests( void );
void	stack_tests( void );
void	set_tests( void );

#endif
