#ifndef __TEST_HPP__
#define __TEST_HPP__

#include "../headers/map.hpp"
#include "../headers/set.hpp"
#include "../headers/stack.hpp"
#include "../headers/vector.hpp"

#include <map>
#include <set>
#include <stack>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <unistd.h>

#define N_TESTS 5
#define N_C_TESTS 4
#define N_V_TESTS 6
#define N_S_TESTS 5
#define N_TEST_USER 5

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
    print_tree_recursion( n->child[ ft::LEFT ], lvl + 1 );
    std::cout << "\n"; indent( lvl + 1 );
    print_tree_recursion( n->child[ ft::RIGHT ], lvl + 1 );
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
std::string value( Value val ) {

    std::stringstream   ss;
    std::string         str_value;

    ss << val << " ";
    std::getline( ss, str_value );
    return str_value;
}

template< class Key, class Value >
std::string value( ft::pair< Key, Value > val ) {

    std::stringstream   ss;
    std::string         str_value;

    ss << " <" << val.first << ", " << val.second << "> ";
    std::getline( ss, str_value );
    return str_value;
}

template< class Key, class Value >
std::string value( std::pair< Key, Value > val ) {

    std::stringstream   ss;
    std::string         str_value;

    ss << " <" << val.first << ", " << val.second << "> ";
    std::getline( ss, str_value );
    return str_value;
}

template< class Iterator >
void iterator_loop( Iterator begin, Iterator end ) {

    if ( begin == end ) {

        std::cout << " [ empty cont. ]\n";
        return ;
    }
    std::cout << " [ ";
    for ( ; begin != end; begin++ ) std::cout << value( *begin );
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

// print header
void header( std::string FUNC_NAME );

// choose test

// get input

#endif
