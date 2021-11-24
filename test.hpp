#ifndef __TEST_HPP__
#define __TEST_HPP__

#include "map.hpp"
#include "set.hpp"
#include "stack.hpp"
#include "vector.hpp"
#include <unistd.h>

#define N_TESTS 5
#define N_C_TESTS 4

#define RED "\033[31m"
#define GREEN "\033[32m"
#define END "\033[0m"
#define BLUE "\033[36m"

void indent( int lvl );

void map_test( void );
void set_test( void );
void stack_test( void );
void vector_test( void );

template< class Node, class Print >
void print_tree_recursion( Node* n, Print print_node, int lvl ) {

    if ( lvl ) std::cout << "-----";
    if ( !n ) {

        std::cout << "<nil> ";
        return ;
    }

    print_node( *n );
    print_tree_recursion( n->child[ ft::left ], lvl + 1 );
    std::cout << "\n"; indent( lvl + 1 );
    print_tree_recursion( n->child[ ft::right ], lvl + 1 );
}

template < class Iterator, class Print >
void print_tree( Iterator it ) {

    std::cout << " --------------- \n";
    print_tree_recursion( it.base( ), 0 );
    std::cout << "\n --------------- \n";
}

template< class Node >
struct node_printer {

    public:
        bool operator( ) ( const Node& n ) {

            if ( n.color( ) == RED ) std::cout << RED;
            std::cout << "< " << n->first << ", " << n->second << " >";
        }
};

template< class Value >
void print_value( Value val ) {

    std::cout << val <<  " ";
}

template< class Key, class Value >
void print_value( ft::pair< Key, Value > val ) {

    std::cout << " ( " << val.first << ", " << val.second << " ) ";
}

template< class Iterator >
void iterator_loop( Iterator begin, Iterator end ) {

    if ( begin == end ) {

        std::cout << " [ empty cont. ]\n";
        return ;
    }
    std::cout << " [ ";
    for ( ; begin != end; begin++ ) print_value( *begin );
    std::cout << "]\n";
}

template< class It >
void rev_iterator_loop( It begin, It end ) {

    if ( begin == end ) {

        std::cout << " [ empty cont. ]\n";
        return ;
    }
    std::cout << " [ ";
    for ( ; begin != end; --end ) print_value( *end );
    std::cout << "]\n";
}

#endif
