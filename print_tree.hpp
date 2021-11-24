#include "tree.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#define RED "\033[31m"
#define GREEN "\033[92m"
#define END "\033[0m"

static void indent( int lvl ) {

    if ( !lvl ) return ;
    for ( int i = 0; i + 1 < lvl; i++ ) {

        std::cout << "     " << "     ";
    }
    std::cout << "     ";
}

template< class Node >
void preorder_print( Node* n, int lvl ) {

    if ( lvl ) std::cout << "-----";
    if ( !n ) {

        std::cout << "<nil> ";
        return ;
    }

    std::cout << *n;
    preorder_print( n->child[ ft::left ], lvl + 1 );
    std::cout << "\n"; indent( lvl + 1 );
    preorder_print( n->child[ ft::right ], lvl + 1 );
}

template< class Tree >
void print( const Tree& tr ) {

    std::cout << "\n------------------\n";
    preorder_print( tr.root( ), 0);
    std::cout << "\n------------------\n";
}