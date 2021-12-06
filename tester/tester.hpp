#ifndef __TESTER_HPP__
#define __TESTER_HPP__

#include <sys/time.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include <iomanip>

#include "stack.hpp"
#include "set.hpp"
#include "vector.hpp"
#include "map.hpp"

#include <stack>
#include <set>
#include <vector>
#include <map>
#include <unistd.h> // debug

#define	CYAN	"\033[33m"
#define	END		"\033[0m"
#define RED		"\033[31m"

#define OK	"\033[32m [ OK ] \033[0m"	
#define KO	"\033[31m [ KO ] \033[0m"
#define ID( x )	CYAN<<"[ "<<x<<" ]"<<END

#define N_TEST 4

#define N_VECTOR_TEST	22
#define N_STACK_TEST	8
#define N_MAP_TEST	20
#define N_SET_TEST	18

template< class ftMap, class stdMap >
void	fill_tree_map( ftMap& fm, stdMap& sm ) {

	for ( int i = 0; i < 1e5; i++ ) {

		int k = rand(), v = rand();

		fm.insert( ft::make_pair(k,v) );
		sm.insert( std::make_pair(k,v) );
	}	
}

template< class ftSet, class stdSet>
void	fill_tree_set( ftSet& fs, stdSet& ss ) {

	for ( int i = 0; i < 1e5; i++ ) {

		int k = rand();

		fs.insert(k);
		ss.insert(k);
	}
}

template< class Map1, class Map2 >
bool	equal_test_map(Map1& fm, Map2& sm){

	int	sum_f_f = 0;
	int	sum_f_s = 0;
	int sum_s_f = 0;
	int sum_s_s = 0;
	if(fm.size() != sm.size()) return false;
	for(typename Map1::iterator it = fm.begin(); it != fm.end(); it++) {
		sum_f_f += it->first;
		sum_f_s += it->second;
	}
	for(typename Map2::iterator it = sm.begin(); it != sm.end(); it++) {
		sum_s_f += it->first;
		sum_s_s += it->second;
	}
	return((sum_f_f == sum_s_f) && (sum_f_s == sum_s_s));
}

template< class Set1, class Set2 >
bool	equal_test_set(Set1& fm, Set2& sm){

	int	sum_f = 0;
	int sum_s = 0;
	if(fm.size() != sm.size()) return false;
	for(typename Set1::iterator it = fm.begin(); it != fm.end(); it++) sum_f += *it;
	for(typename Set2::iterator it = sm.begin(); it != sm.end(); it++) sum_s += *it;
	return sum_f == sum_s;
}

/* ================= PRINT TREE =================== */

namespace ft {

template< class T >
void print_node( T n, typename ft::enable_if< ft::is_integral< T >::value, T >::type* switch_on = NULL ) {
	( void )switch_on;
	std::cout << "< " << n << " >";
}

template< class T1, class T2 >
void print_node( ft::pair< T1, T2 > n ) {
	std::cout << "< " << n.first << " >";
}

template< class Node >
void print_recursion( Node* n, int lvl ) {

	if( lvl ) std::cout << "-----";
	if ( !n ) {
		std::cout << "<nil>";
		return ;
	}
	if( n->color( ) == 1 ) 
		std::cout << RED; 
	print_node( *( *n ) ); std::cout << END;
	print_recursion( n->child[0], lvl + 1 );
	std::cout << "\n";
	for( int i = 0; i < lvl; i++ ) 
		std::cout << "          ";
	std::cout << "     ";
	print_recursion( n->child[1], lvl + 1 );
}

template< class Tree >
void	print( Tree& tr ) {

	typename Tree::iterator	it = tr.begin( );

	std::cout << "\n-*****************-\n";
	print_recursion( it.get_last_node( )->parent, 0 );
	std::cout << "\n-*****************-\n";
}

}

/* ================================================== */

template< class T, class Cont = ft::vector< T > >
class MutantStack : public ft::stack< T, Cont > {

	public:
	
	typedef	typename Cont::iterator					iterator;
	typedef typename Cont::const_iterator			const_iterator;
	typedef typename Cont::reverse_iterator			reverse_iterator;
	typedef typename Cont::const_reverse_iterator	const_reverse_iterator;

	MutantStack( void ) : ft::stack< T, Cont >( ) { }
	MutantStack( const MutantStack& other ) : ft::stack< T, Cont >( other ) { }
	MutantStack( const Cont& cont) : ft::stack< T, Cont >( cont ) { }
	~MutantStack( ) { }

	iterator	begin( void ) { return this->c.begin( ); }
	iterator	end( void ) { return this->c.end( ); }

	const_iterator begin( void ) const { return this->c.begin( ); }
	const_iterator end( void ) const { return this->c.end( ); }

	reverse_iterator	rbegin( void ) { return this->c.rbegin( ); }
	reverse_iterator	rend( void ) { return this->c.rend( ); }

	const_reverse_iterator	rbegin( void ) const { return this->c.rbegin( ); }
	const_reverse_iterator	rend( void ) const { return this->c.rend( ); }
};

void	vector_tests( void );
void	map_tests( void );
void	stack_tests( void );
void	set_tests( void );

long	get_time( void );

#endif
